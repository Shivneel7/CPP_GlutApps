#pragma once

#include "Sprite.h"

enum ID { fruit, bomb, player };

// This is a base class for any object that moves
class MovingSprite : public Sprite {
  protected:
    float dx, dy;
    ID id;

  public:
    MovingSprite(const char *filename, int rows, int cols, float x, float y, float w, float h, float dx, float dy, ID id);

    virtual void idle();

    void setDX(float dx);
    float getDX() const;

    void setDY(float dy);
    float getDY() const;

    ID getID();
};