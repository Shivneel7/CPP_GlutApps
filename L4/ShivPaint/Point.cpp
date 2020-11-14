#include "Point.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Point::Point(float x, float y, float r, float g, float b, int w): x(x), y(y), r(r), g(g), b(b) ,w(w){}

Point::Point(Point &other): x(other.x), y(other.y), w(other.w), r(other.r), g(other.g), b(other.b){}

void Point::draw(){
    glColor3f(r, g, b);
    glPointSize(w);

    glBegin(GL_POINTS);

    glVertex2f(x, y);

    glEnd();
}

