#pragma once

#include "Text.h"

// Displays all non moving HUD components
class HUD {
    Text *scoreText;
    int score;

  public:
    HUD();
    void increaseScore();

    void draw(float z = 0) const;
};
