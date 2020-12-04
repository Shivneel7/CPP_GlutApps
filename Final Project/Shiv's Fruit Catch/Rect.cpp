#include "Rect.h"
#include "GlutApp.h"

Rect::Rect(){
	x = 0;
	y = 0;
	w = 0.5;
	h = 0.5;
	r = 1; 
	g = 0;
	b = 0;
}

Rect::Rect(float x, float y, float w, float h, float r, float g, float b){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;
}

void Rect::draw(float z) const {
	glColor3f(r, g, b);

	glBegin(GL_POLYGON);

	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y-h);
	glVertex2f(x, y-h);

	glEnd();
}


void Rect::setY(float y){
	this-> y = y;
}

void Rect::setX(float x){
	this-> x = x;
}

float Rect::getY() const {
	return y;
}

float Rect::getX() const {
	return x;
}

void Rect::setW(float w){
	this-> w = w;
}

void Rect::setH(float h){
	this-> h = h;
}

float Rect::getW() const {
	return w;
}

float Rect::getH() const {
	return h;
}

bool Rect::contains(float x, float y) const{
	return x >= this->x && x <= this->x + w && y <= this->y && y >= this->y - h;
}

bool Rect::checkCollision(const Rect& two) const{
    return  (this->getX() < (two.getX() + two.getW()) && two.getX() < (this->getX() + this->getW())) &&
            (this->getY() > (two.getY() - two.getH()) && two.getY() > (this->getY() - this->getH()));
}
