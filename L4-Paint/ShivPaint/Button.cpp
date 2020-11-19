#include "Button.h"
#include <iostream>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Button::Button(float x, float y, float w, float h, float r, float g, float b, std::string text, float tXO, float tYO, bool displayText): x(x), y(y), w(w), h(h), r(r), g(g), b(b), text(text), tXO(tXO), tYO(tYO), displayText(displayText), font(GLUT_BITMAP_9_BY_15){}

Button::Button(const Button& other): x(other.x), y(other.y), w(other.w), h(other.h), r(other.r), g(other.g), b(other.b), text(other.text),tXO(other.tXO), tYO(other.tYO), displayText(other.displayText), font(GLUT_BITMAP_TIMES_ROMAN_10){}

void Button::draw(int windowW, int windowH){
    if(displayText){
        glColor3f(0, 0, 0);
        float offset = 0;

        for (int i = 0; i < text.length(); i++) {
            glRasterPos2f(x+tXO+offset, y-2*(float)glutBitmapHeight(font)/windowH);
            // glRasterPos2f(x+tXO+offset, y - tYO);
            glutBitmapCharacter(font, text[i]);
            offset += (2*(float)glutBitmapWidth(font, text[i]) / windowW);
        }
    }

    glColor3f(r, g, b);

    glBegin(GL_POLYGON);

    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y-h);
    glVertex2f(x, y-h);

    glEnd();

}

bool Button::contains(float mx, float my){
	return (mx >= this->x) && (mx <= this->x + this->w) && (my <= this->y) && (my >= this->y - this->h);
}

void Button::changeColor(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}