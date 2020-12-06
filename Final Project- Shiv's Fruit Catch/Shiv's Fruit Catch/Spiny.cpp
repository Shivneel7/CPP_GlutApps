#include "Spiny.h"

Spiny::Spiny() : Sprite("spiny.png", 1, 16, .85, 1.2, .15, .15, 0, -.01, true, spiny) {
    spawnLeft = rand()%2;
    if (spawnLeft) {
        x = -1;
    } else {
        x = .85;
    }
}

Spiny::Spiny(bool f) : Sprite("spiny.png", 1, 16, .85, 1.2, .15, .15, 0, -.01, true, spiny) {
    if (spawnLeft) {
        x = -1;
    } else {
        x = .85;
    }
}

void Spiny::idle() {
    MovingTexRect::idle();
    advance();
    if (y < -.65) {
        y = -.65;
        dy = 0;
        if (spawnLeft) {
            dx = .01;
        } else {
            dx = -.01;
        }
    }
}
