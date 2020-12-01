#include "Text.h"
#include "GlutApp.h"

Text::Text(float x, float y, std::string text, float r, float g, float b) :Rect(x, y, 0, 0, r, g, b), text(text), font(GLUT_BITMAP_TIMES_ROMAN_24), windowW(600), windowH(600) {
}

void Text::draw(float z) const {
    glColor3f(r, g, b);
    float offset = 0;

    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x + offset, y - 2 * (float)glutBitmapHeight(font) / windowH);
        // glRasterPos2f(x+tXO+offset, y - tYO);
        glutBitmapCharacter(font, text[i]);
        offset += (2 * (float)glutBitmapWidth(font, text[i]) / windowW);
    }
}
