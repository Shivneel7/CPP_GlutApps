#pragma once

#include "MovingTexRect.h"

/** A Moving Sprite object with added functionality:
 * 
 * has a modified idle so that player can jump and is affected by gravity
 *
 * players sprite behaves a bit differently than other sprites
 *
 * "holds" a basket (contains a pointer to another MovingSprite so that only
 *  the basket portion of the player model collects fruit)
 */
class Player : public MovingTexRect {

    MovingTexRect *basket;

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
    bool checkBasketCollision(const Rect &two);
};
