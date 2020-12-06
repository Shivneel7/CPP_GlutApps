#pragma once

#include "Bar.h"
#include "Text.h"
#include <vector>

// Displays all non moving HUD components
class HUD {
    static const int TOTAL_HEALTH_POINTS = 5;

    Text *fruitCollectedText;
    Text *fruitDroppedText;

    Bar *healthBar;
    Bar *energyBar;

    std::vector<Rect *> hudComponents;

    int fruitCollected;
    int fruitDropped;

  public:
    HUD();
    HUD(HUD &other);

    void increaseScore(int amount);

    void droppedFruit();

    void increaseHealth();
    void decreaseHealth();
    bool healthIsEmpty() const;

    void increaseEnergy();
    void decreaseEnergy();
    void replenishEnergy();
    bool hasEnergy() const;

    void draw(float z = 0) const;

    ~HUD();
};
