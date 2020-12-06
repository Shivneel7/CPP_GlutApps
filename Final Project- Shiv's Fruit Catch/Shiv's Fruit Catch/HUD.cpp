#include "HUD.h"

HUD::HUD() {
    score = 0;
    scoreText = new Text(.4, -.8, "Score: 0");
    healthBar = new Bar("health-full2.png", -.95, -.85, .5, .15, "health-empty2.png", 1);
    energyBar = new Bar("energy-full.png", -.3, -.85, .5, .15, "energy-empty.png", 0);

    hudComponents.push_back(scoreText);
    hudComponents.push_back(healthBar);
    hudComponents.push_back(energyBar);
}

HUD::HUD(HUD &other) : scoreText(other.scoreText), score(score), healthBar(other.healthBar) {
}

void HUD::increaseScore(int amount) {
    score += amount;
    scoreText->setText("Score: " + std::to_string(score));
}

void HUD::increaseHealth() {
    healthBar->increment(1.0 / 6);
}

void HUD::decreaseHealth() {
    healthBar->increment(-1.0 / 6);
}

void HUD::increaseEnergy() {
    energyBar->increment(.25);
}

void HUD::decreaseEnergy() {
    energyBar->increment(-.005);
}

bool HUD::hasEnergy() const {
    return energyBar->getPercent() > 0;
}

void HUD::draw(float z) const {
    for (Rect *t : hudComponents) {
        t->draw(z);
    }
}

bool HUD::healthIsEmpty() const {
    return healthBar->getPercent() == 0;
}

HUD::~HUD() {
    for (Rect *t : hudComponents) {
        delete t;
    }
}
