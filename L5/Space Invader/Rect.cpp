#include <math.h>
#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Rect::Rect(){
	x = -0.1;
	y = 0.1;
	red = 1;
	green = 1;
	blue = 1;

	w = 0.2;
	h = 0.2;
}

Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;

	red = 1;
	green = 1;
	blue = 1;

	this->w = w;
	this->h = h;
}

Rect::Rect(float x, float y, float w, float h, float red, float green, float blue){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;
}

Rect::Rect(const Rect& other){
	x = other.x;
	y = other.y;

	red = other.red;
	green = other.green;
	blue = other.blue;

	w = other.w;
	h = other.h;
}

bool Rect::operator== (const Rect& other){
	return 	x == other.x && 
			y == other.y && 
			h == other.h && 
			red == other.red && 
			green == other.green && 
			blue == other.blue;
}

Rect::~Rect(){
	// There is nothing to do here for now...
}

bool Rect::contains(float x, float y) const {
	return (x > this->x) && (x < this->x + this->w) && (y < this->y) && (y > this->y - this->h);
}


void Rect::draw(){

	glColor3f(red, green, blue);
	
	glBegin(GL_POLYGON);

	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y-h);
	glVertex2f(x, y-h);

	glEnd();
	
}

float Rect::getX() const {
	return x;
}

float Rect::getY() const {
	return y;
}

float Rect::getW() const {
	return w;
}

float Rect::getH() const {
	return h;
}

float Rect::getR() const {
	return red;
}

float Rect::getG() const {
	return green;
}

float Rect::getB() const {
	return blue;
}

void Rect::setX(float x){
	this->x = x;
}

void Rect::setY(float y){
	this->y = y;
}

void Rect::setW(float w){
	this->w = w;
}

void Rect::setH(float h){
	this->h = h;
}
