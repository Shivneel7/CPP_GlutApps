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

    // The original bounds of the mario texture was too large, so, I made this rectangle which acts as an artifical boundary box for collision detection
    Rect *bounds;

    Rect *basketBounds;


    bool facingLeft;
    bool speedBoost;
    bool moving;
    bool jumping;
    bool debugMode;
    // Used so Player doesnt take multiple damage ticks when in contact with a persistance damage source
    bool showPlayer, invulnerable;
    int invulnerableCount;

  public:
    Player(bool);

    void draw(float z = 0) const;
    void idle();
    void jump();
    void advance();

    // facing left is 1, facing right is 0;
    void setIsFacingLeft(bool b);

    void setSpeedBoost(bool b);
    bool isSpeedBoosted() const;

    bool isMoving() const;

    void setInvulnerable(bool b);
    bool isInvulnerable() const;

    bool checkBasketContains(float, float);
    bool checkBasketCollision(const Rect &two);

    // for changing the bounds of
    virtual bool checkCollision(const Rect &r) const;

    virtual void showBounds() const;

    ~Player();
};
