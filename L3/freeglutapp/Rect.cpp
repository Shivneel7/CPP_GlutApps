#include "Rect.h"
#include <math.h>
#include <iostream>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Rect::Rect(){
	x = 0;
	y = 0;
	red = 1;
	green = 0;
	blue = 0;

	w = 0.2;
	h = 0.2;
	
	num = 0;

	selected = false;
	resizing = false;
}

Rect::Rect(float x, float y, float w, float h, float red, float green, float blue, int num){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;

	this->num = num;

	selected = false;
	resizing = false;
}

bool Rect::contains(float x, float y){
	return (x > this->x) && (x < this->x + this->w) && (y < this->y) && (y > this->y - this->h);
}

void Rect::draw(){
	
	glColor3f(red,green,blue);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, 0.1);
	glVertex3f(x+w, y, 0.1);
	glVertex3f(x+w, y-h, 0.1);
	glVertex3f(x, y-h, 0.1);

	glEnd();

	if(selected){
		glColor3f(1,1,1);
		glBegin(GL_LINES);

		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);

		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);

		glEnd();
	}
}

void Rect::select(){
	selected = true;
}

void Rect::deselect(){
	selected = false;
}