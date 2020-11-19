#ifndef BUTTON_H
#define BUTTON_H

#include <string>

struct Button{
    float x,y;

	float w,h;

	float r,g,b;

    std::string text;
    void* font;

    //x and y offsets for text so they fit in the rectangle
    float tXO, tYO;
    bool displayText;

    Button(float x=0, float y=0, float w=.3, float h=.3, float r=0, float g=0, float b=1, std::string text="", float tXO=0, float tYO=0, bool displayText = false); 
    Button(const Button& other);
    
    void draw(int width, int height);

    bool contains(float x, float y);

    void changeColor(float r, float g, float b);
};

#endif
