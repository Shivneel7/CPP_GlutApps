#pragma once

#include "TexRect.h"

// This is a base class for any object that moves
class MovingTexRect : public TexRect {
    float dx, dy, speed;

  public:
    MovingTexRect(const char *filename, float x, float y, float w, float h, float dx, float dy, float speed);

    void idle();
    void setDX(float dx);
    float getDX() const;
    void setDY(float dy);
    float getDY() const;
    void setSpeed(float speed);
    float getSpeed() const;
};
