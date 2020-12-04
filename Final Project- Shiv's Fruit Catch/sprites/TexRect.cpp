#include "TexRect.h"
#include <iostream>

TexRect::TexRect(const char* filename, float x=0, float y=0, float w=0.5, float h=0.5): Rect(x, y, w, h, 1.0f, 1.0f, 1.0f){

    std::cout << "Loading " << filename << std::endl;
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    int wi, hi, c;
    
    unsigned char * test = SOIL_load_image(filename, &wi, &hi, &c, SOIL_LOAD_AUTO);
    
    texture_id = SOIL_load_OGL_texture (
                                        filename,
                                        SOIL_LOAD_AUTO,
                                        SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB 
                                        );
    
    if(0 == texture_id){
        std::cout <<"SOIL loading error: " << SOIL_last_result() << std::endl;
    }
    
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texwidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texheight);
    
    int width, height;
    FILE *image;
    int size, i = 0;
    unsigned char *data;
    
    image =fopen(filename,"rb");  // open JPEG image file
    if(!image){
        printf("Unable to open image \n");
    }
    fseek(image,  0,  SEEK_END);
    size = ftell(image);
    fseek(image,  0,  SEEK_SET);
    data = (unsigned char *)malloc(size);
    fread(data, 1, size, image);
    /* verify valid JPEG header */
    if(data[i] == 0xFF && data[i + 1] == 0xD8 && data[i + 2] == 0xFF && data[i + 3] == 0xE0) {
        i += 4;
        /* Check for null terminated JFIF */
        if(data[i + 2] == 'J' && data[i + 3] == 'F' && data[i + 4] == 'I' && data[i + 5] == 'F' && data[i + 6] == 0x00) {
            while(i < size) {
                i++;
                if(data[i] == 0xFF){
                    if(data[i+1] == 0xC0) {
                        height = data[i + 5]*256 + data[i + 6];
                        width = data[i + 7]*256 + data[i + 8];
                        break;
                    }
                }
            }
        }
    }

    fclose(image);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void TexRect::draw(float z) const {
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x, y - h, z);
    
    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);
    
    glTexCoord2f(1, 1);
    glVertex3f(x+w, y, z);
    
    glTexCoord2f(1, 0);
    glVertex3f(x+w, y - h, z);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
