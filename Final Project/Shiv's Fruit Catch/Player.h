#pragma once

#include "MovingTexRect.h"

class Player : public MovingTexRect {
    const float BASE_SPEED;
    float dx, dy, speed;

    // facing left is 1, facing right is 0;
    bool direction;

  public:
    Player();

    void draw(float z = 0) const;
    void jump();

    // facing left is 1, facing right is 0;
    void setDirection(bool b);
};
