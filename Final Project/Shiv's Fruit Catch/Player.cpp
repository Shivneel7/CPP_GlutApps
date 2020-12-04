#include "Player.h"
#include "iostream"

Player::Player() : MovingTexRect("skeleton1.png", -.1, -.62, .3, .4, 0, 0, player), direction(0), isFaster(0), basket(new MovingTexRect("basket1.png", -.1, -.72, .3, .1, 0, 0, defaultID)) {
    // left = 0.05;
    // right = .27;
    // top = .3;
    // bottom = 0;
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

    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0.05, 0);
    glVertex3f(x, y - h, z);

    glTexCoord2f(0.05, .3);
    glVertex3f(x, y, z);

    glTexCoord2f(.27, .3);
    glVertex3f(x + w, y, z);

    glTexCoord2f(.27, 0);
    glVertex3f(x + w, y - h, z);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // basket->draw();

    // MovingTexRect::draw();
    basket->draw();
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
    if (y < -.6) {
        y = -.6;
    }
    basket->setX(x);
    basket->setY(y-.125);

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

bool Player::checkBasketCollision(const Rect &two) {
    basket->checkCollision(two);
}