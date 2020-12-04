#include "MovingTexRect.h"

MovingTexRect::MovingTexRect(const char *filename, float x = 0, float y = 0, float w = 0.5, float h = 0.5, float dx = 0, float dy = 0, ID id = defaultID) : TexRect(filename, x, y, w, h), dx(dx), dy(dy), id(id) {
}

void MovingTexRect::idle() {
    x += dx;
    y += dy;
}

void MovingTexRect::setDX(float dx) {
    this->dx = dx;
}

float MovingTexRect::getDX() const {
    return dx;
}

void MovingTexRect::setDY(float dy) {
    this->dy = dy;
}

float MovingTexRect::getDY() const {
    return dy;
}

ID MovingTexRect::getID() {
    return id;
}
