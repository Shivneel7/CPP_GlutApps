#pragma once

#include "MovingSprite.h"

class Player : public MovingSprite {
    // facing left is 1, facing right is 0;
    bool direction;
    bool isFaster;
  public:
    Player();

    void draw(float z = 0) const;
    void idle();
    void jump();

    // facing left is 1, facing right is 0;
    void setDirection(bool b);
    void setIsFaster(bool b);
};
