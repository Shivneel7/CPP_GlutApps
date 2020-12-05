#pragma once

#include "Sprite.h"

/** A Moving Sprite object with added functionality:
 * 
 * has a modified idle so that player can jump and is affected by gravity
 *
 * players sprite behaves a bit differently than other sprites
 *
 * "holds" a basket (contains a pointer to another MovingSprite so that only
 *  the basket portion of the player model collects fruit)
 */
class Player : public Sprite {

    MovingTexRect *basket;
    Rect* bounds;
    // facing left is 1, facing right is 0;
    bool facingLeft;
    bool speedBoost;
    bool moving;

  public:
    Player();

    void draw(float z = 0) const;
    void idle();
    void jump();
    void advance();
    // facing left is 1, facing right is 0;
    void setIsFacingLeft(bool b);
    void setIsFaster(bool b);
    bool isMoving();

    bool checkBasketContains(float, float);
    bool checkBasketCollision(const Rect &two);
};
