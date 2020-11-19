#include "Rect.h"
#include <math.h>

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
	green = 1;
	blue = 1;

	w = 0.2;
	h = 0.2;

	mark = ' ';
}

Rect::Rect(float x, float y, float w, float h, char mark){
	this->x = x;
	this->y = y;

	red = 1;
	green = 1;
	blue = 1;

	this->w = w;
	this->h = h;

	this->mark = mark;
}

Rect::Rect(float x, float y, float w, float h, float red, float green, float blue, char mark){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;

	this->mark = mark;
}

void Rect::draw(){

	//draw x
	if(mark == 'x'){ 
		glLineWidth(5); 

		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		

		glVertex2f(x + .01, y - 0.01);
		glVertex2f(x+w-.01, y-h+.01);
		
		glVertex2f(x+w-.01, y- 0.01);
		glVertex2f(x+.01, y-h+.01);

		glEnd();
		
	}else if(mark == 'o'){//draw the circle

		glPointSize(5);

		glColor3f(0,0,1);

		glBegin(GL_POINTS);

		float theta = 0;
		float inc = M_PI/100;

		for (theta; theta <= 2*M_PI; theta += inc){
			glVertex2f(cos(theta)*w *.45 + x + w/2, sin(theta)*h*.45 + y - h/2);
		} 
		glEnd();
	}else if(mark == '1'){
		glLineWidth(5); 

		glColor3f(0,0,0);
		glBegin(GL_LINES);

		//A
		float aOffset = .45;
		glVertex2f(x + w  * aOffset, y - 0.01);
		glVertex2f(x + w  * aOffset - .1, y-h+.01);
		
		glVertex2f(x + w  * aOffset, y - 0.01);
		glVertex2f(x + w  * aOffset + .1, y-h+.01);

		glVertex2f(x + w  * aOffset - .05, y-h/2);
		glVertex2f(x + w  * aOffset + .05, y-h/2);

		//I
		glVertex2f(x + w  * (aOffset + .2), y - 0.01);
		glVertex2f(x + w  * (aOffset + .2), y-h+.01);

		glEnd();
	}else if(mark == '2'){
		glLineWidth(5); 

		glColor3f(0,0,0);
		glBegin(GL_LINES);

		//I
		glVertex2f(x + w  *  .45, y - 0.01);
		glVertex2f(x + w  *  .45, y-h+.01);

		glVertex2f(x + w  *  .55, y - 0.01);
		glVertex2f(x + w  *  .55, y-h+.01);

		glEnd();
	}

	glColor3f(red, green, blue);

	glBegin(GL_POLYGON);

	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y-h);
	glVertex2f(x, y-h);

	glEnd();


}

void Rect::select(char mark){
	this->mark = mark;
}

bool Rect::contains (float mx, float my){
	return mx >= x && mx <= x + w && my <= y && my >= y - h;
}

bool Rect::isBlank(){
	return mark == ' ';
}