#include "Circle.h"
#include "GlutApp.h"
#include <cmath>

Circle::Circle(){
	x = 0.0;
	y = 0.0;
	radius = 0.2;
	r = 0.0;
	g = 0.0;
	b = 1.0;
}

void Circle::draw(float z) const {
	float theta = 0;
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);

    float inc = M_PI/50;

    for (theta; theta < 2 * M_PI; theta += inc){
        glVertex3f(radius*cos(theta), radius*sin(theta), z);
    }

    glEnd();
}
