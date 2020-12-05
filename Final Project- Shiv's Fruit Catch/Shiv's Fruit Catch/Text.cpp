#include "Text.h"
#include "GlutApp.h"

Text::Text(float x, float y, std::string text) : Rect(x, y, 0, 0, 1, 1, 1), showRectangle(false), text(text), font(GLUT_BITMAP_TIMES_ROMAN_24), windowW(600), windowH(600) {
}

Text::Text(float x, float y, std::string text, float r, float g, float b) : Rect(x, y, 0, 0, r, g, b), showRectangle(false), text(text), font(GLUT_BITMAP_TIMES_ROMAN_24), windowW(600), windowH(600) {
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

void Text::setText(std::string t) {
    text = t;
}