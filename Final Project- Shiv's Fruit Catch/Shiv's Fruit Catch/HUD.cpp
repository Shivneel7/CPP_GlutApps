#include "HUD.h"

HUD::HUD() {
    score = 0; 
    health = 1;
    scoreText = new Text(.4, -.8, "Score: 0");
    healthBar = new Bar("health1.png", -.95, -.9, .5, .1);

}

HUD::HUD(HUD &other) : scoreText(other.scoreText), score(score), health(other.health), healthBar(other.healthBar) {
}

void HUD::increaseScore() {
    score++;
    scoreText->setText("Score: " + std::to_string(score));
}

void HUD::decreaseHealth() {
    health -= .1;
    healthBar->setRight(health);
}

void HUD::draw(float z) const {
    scoreText->draw(z);
    healthBar->draw(z);
}

HUD::~HUD() {
    delete scoreText;
}
