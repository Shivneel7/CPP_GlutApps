#include "HUD.h"

HUD::HUD() {
    fruitCollected = 0;
    fruitDropped = 0;

    fruitCollectedText = new Text(.3, -.8, "Fruits Collected: 0", 44 / 255.0, 169 / 255.0, 82 / 255.0);
    hudComponents.push_back(fruitCollectedText);

    fruitDroppedText = new Text(.3, -.88, "Fruits Dropped: 0", 1, 0, 0);
    hudComponents.push_back(fruitDroppedText);

    healthBar = new Bar("health-full.png", -.99, -.85, .55, .125, "health-empty.png", 1);
    hudComponents.push_back(healthBar);

    energyBar = new Bar("energy-full.png", -.35, -.85, .55, .125, "energy-empty.png", 1);
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
    healthBar->increment(1.0 / TOTAL_HEALTH_POINTS);
}

void HUD::decreaseHealth() {
    healthBar->increment(-1.0 / TOTAL_HEALTH_POINTS);
}

void HUD::increaseEnergy() {
    energyBar->increment(.25);
}

void HUD::decreaseEnergy() {
    energyBar->increment(-.003);
}

void HUD::lose() {
    fruitCollectedText->setX(-.5);
    fruitCollectedText->setY(.3);
    fruitCollectedText->setColor(0,100/255.0,0);
    fruitCollectedText->setText("Good Job, You Collected " + std::to_string(fruitCollected) + " Fruit!");

    fruitDroppedText->setX(-.8);
    fruitDroppedText->setY(0.1);
    fruitDroppedText->setColor(193 / 255.0, 42 / 255.0, 42 / 255.0);
    fruitDroppedText->setText("Unfortunately, you also let " + std::to_string(fruitDropped) + " fruit touch the ground...");
}

void HUD::replenishEnergy() {
    energyBar->increment(1);
}

bool HUD::hasEnergy() const {
    return !energyBar->isEmpty();
}

void HUD::draw(float z) const {
    for (Rect *t : hudComponents) {
        t->draw(z);
    }
}

bool HUD::healthIsEmpty() {
    if (healthBar->isEmpty()) {
        lose();
    }
    return healthBar->isEmpty();
}

HUD::~HUD() {
    for (Rect *t : hudComponents) {
        delete t;
    }
}
