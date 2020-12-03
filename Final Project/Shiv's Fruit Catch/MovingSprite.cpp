#include "MovingSprite.h"

MovingSprite::MovingSprite(const char *filename, int rows = 1, int cols = 1, float x = 0, float y = 0, float w = 0.5, float h = 0.5, float dx = 0, float dy = 0, ID id = fruit) : Sprite(filename, rows, cols, x, y, w, h), dx(dx), dy(dy), id(id) {
}

void MovingSprite::idle() {
    x += dx;
    y += dy;
}

void MovingSprite::setDX(float dx) {
    this->dx = dx;
}

float MovingSprite::getDX() const {
    return dx;
}

void MovingSprite::setDY(float dy) {
    this->dy = dy;
}

float MovingSprite::getDY() const {
    return dy;
}

ID MovingSprite::getID() {
    return id;
}
