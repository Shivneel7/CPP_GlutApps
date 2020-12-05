#include "Bar.h"

// have a texture, the "right" attribute depletes with time.

Bar::Bar(const char *filename, float x, float y, float w, float h) : TexRect(filename, x, y, w, h), right(1) {
}

void Bar::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x, y - h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(right, 1);
    glVertex3f(x + w - (1 - right)*w, y, z);

    glTexCoord2f(right, 0);
    glVertex3f(x + w - (1 - right)*w, y - h, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Bar::setRight(float right) {
    this->right = right;
}
