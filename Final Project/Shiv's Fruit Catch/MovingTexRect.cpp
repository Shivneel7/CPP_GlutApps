#include "MovingTexRect.h"

MovingTexRect::MovingTexRect(const char *filename, float x = 0, float y = 0, float w = 0.5, float h = 0.5, float dx = 0, float dy = 0, float speed = 0): TexRect(filename,x, y, w, h), dx(dx), dy(dy), speed(speed){
}

void MovingTexRect::idle() {
    x += dx;
    y += dy;
}

void MovingTexRect::setDX(float dx) {
    this->dx = dx;
}

float MovingTexRect::getDX() const{
    return dx;
}

void MovingTexRect::setDY(float dy) {
    this->dy = dy;
}

float MovingTexRect::getDY() const{
    return dy;
}

void MovingTexRect::setSpeed(float speed) {
    this->speed = speed;
}

float MovingTexRect::getSpeed() const{
    return speed;
}
