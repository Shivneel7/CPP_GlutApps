#pragma once

#include "Bar.h"
#include "Text.h"
#include <vector>

/** Keeps track of score, health, energy
 *  draws all nonmoving components that display text stats (e.g health, energy)
 */
class HUD : public Shape {
    static const int TOTAL_HEALTH_POINTS = 5;

    Text *fruitCollectedText;
    Text *fruitDroppedText;
    Text *timerText;

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

    void setSeconds(int s);

    void increaseHealth();

    /** decreaseHealth, returns true if health is empty.
     * @return true if health is empty after decreasing
     */
    bool decreaseHealth();
    bool healthIsEmpty();

    void increaseEnergy();
    void decreaseEnergy();
    void replenishEnergy();
    bool hasEnergy() const;

    void lose();

    void draw(float z = 0) const;

    ~HUD();
};
