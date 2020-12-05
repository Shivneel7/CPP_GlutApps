#pragma once

#include "Bar.h"
#include "Text.h"
// Displays all non moving HUD components
class HUD {
    Text *scoreText;
    Bar *healthBar;
    float health;
    int score;

  public:
    HUD();
    HUD(HUD &other);

    void increaseScore();
    void decreaseHealth();

    void draw(float z = 0) const;

    ~HUD();
};
