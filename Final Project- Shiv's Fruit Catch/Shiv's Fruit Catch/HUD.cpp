#include "HUD.h"

HUD::HUD() {
    scoreText = new Text(.4, -.8, "Score: 0");
}

void HUD::increaseScore() {
    score++;
    scoreText->setText("Score: " + std::to_string(score));
}

void HUD::draw(float z) const{
    scoreText->draw();
}