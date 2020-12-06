#pragma once;

#include "Sprite.h"

class Spiny : public Sprite {
  protected:
    bool spawnLeft;

  public:
    Spiny();
    Spiny(bool spawnLeft);

    virtual void idle();
};