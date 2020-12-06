#include "HUD.h"

HUD::HUD() {
    fruitCollected = 0;
    fruitDropped = 0;

    fruitCollectedText = new Text(.3, -.8, "Fruits Collected: 0", 44/255.0, 169/255.0, 82/255.0);
    hudComponents.push_back(fruitCollectedText);

    fruitDroppedText = new Text(.3, -.88, "Fruits Dropped: 0", 1, 0, 0);
    hudComponents.push_back(fruitDroppedText);

    healthBar = new Bar("health-full.png", -.99, -.88, .5, .1, "health-empty.png", 1);
    hudComponents.push_back(healthBar);

    energyBar = new Bar("energy-full.png", -.39, -.88, .5, .1, "energy-empty.png", 1);
    hudComponents.push_back(energyBar);
}

HUD::HUD(HUD &other) : fruitCollectedText(other.fruitCollectedText), fruitCollected(fruitCollected), healthBar(other.healthBar) {
}

void HUD::increaseScore(int amount) {
    fruitCollected += amount;
    fruitCollectedText->setText("Fruits Collected: " + std::to_string(fruitCollected));
}

void HUD::droppedFruit() {
    fruitDropped++;
    fruitDroppedText->setText("Fruits Dropped: " + std::to_string(fruitDropped));
}

void HUD::increaseHealth() {
    healthBar->increment(1.0 / 5);
}

void HUD::decreaseHealth() {
    healthBar->increment(-1.0 / 5);
}

void HUD::increaseEnergy() {
    energyBar->increment(.25);
}

void HUD::decreaseEnergy() {
    energyBar->increment(-.005);
}

bool HUD::hasEnergy() const {
    return !energyBar->isEmpty();
}

void HUD::draw(float z) const {
    for (Rect *t : hudComponents) {
        t->draw(z);
    }
}

bool HUD::healthIsEmpty() const {
    return healthBar->isEmpty();
}

HUD::~HUD() {
    for (Rect *t : hudComponents) {
        delete t;
    }
}
