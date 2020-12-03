#include "Player.h"
#include "iostream"

Player::Player() : MovingSprite("player-idle.png", 1, 1, -.1, -.72, .3, .3, 0, 0, player), direction(0), isFaster(0) {
}

void Player::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    // glColor4f(1, 1, 1, 1);

    // if (!direction) {
    //     glTexCoord2f(1, 0);
    //     glVertex3f(x, y - h, z);

    //     glTexCoord2f(1, 1);
    //     glVertex3f(x, y, z);

    //     glTexCoord2f(0, 1);
    //     glVertex3f(x + w, y, z);

    //     glTexCoord2f(0, 0);
    //     glVertex3f(x + w, y - h, z);
    // } else {
    //     glTexCoord2f(0, 0);
    //     glVertex3f(x, y - h, z);

    //     glTexCoord2f(0, 1);
    //     glVertex3f(x, y, z);

    //     glTexCoord2f(1, 1);
    //     glVertex3f(x + w, y, z);

    //     glTexCoord2f(1, 0);
    //     glVertex3f(x + w, y - h, z);
    // }

    //~~~~~~~~~~~~~~~~~~~~~~~TEST-----------=============

    //Shows half the player with the full box. to see half the player correctly sized, make w = w/2
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x, y - h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(.5, 1);
    glVertex3f(x + w, y, z);

    glTexCoord2f(.5, 0);
    glVertex3f(x + w, y - h, z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Player::idle() {
    x += dx;

    if (isFaster) {
        x += dx;
    }

    if (x < -1) {
        x = -1;
    }
    if (x > 1 - w) {
        x = 1 - w;
    }
    y += dy;
    dy -= .001;
    if (y < -.7) {
        y = -.7;
    }
}

void Player::jump() {
    dy = .02;
}

void Player::setDirection(bool b) {
    direction = b;
}

void Player::setIsFaster(bool b) {
    isFaster = b;
}
