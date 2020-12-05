#include "Player.h"
#include "iostream"

Player::Player() : Sprite("player.png", 1, 8, -.1, -.62, .25, .3, 0, 0, player), facingLeft(0), speedBoost(0), basket(new MovingTexRect("basket1.png", -.1, -.72, .2, .1, 0, 0, defaultID)) {
    // left = 0;
    // right = 0.125;
    // // temporarily using these. fix once sprite sheet class is fixed

    // // flashing
    // // int row = 2;
    // // cols = 2;

    // // walking
    // // int row = 0;
    // // cols = 8;
    // // bottom = row * .1;
    // // top = bottom + .1;

    // // walking
    // cols = 8;
    // bottom = 0;
    // top = 1;
}

void Player::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    ///////////mario.png//////////////////
    glColor4f(1, 1, 1, 1);

    if (facingLeft) {
        glTexCoord2f(left, bottom);
        glVertex3f(x, y - h, z);

        glTexCoord2f(left, top);
        glVertex3f(x, y, z);

        glTexCoord2f(right, top);
        glVertex3f(x + w, y, z);

        glTexCoord2f(right, bottom);
        glVertex3f(x + w, y - h, z);
    } else {
        glTexCoord2f(right, bottom);
        glVertex3f(x, y - h, z);

        glTexCoord2f(right, top);
        glVertex3f(x, y, z);

        glTexCoord2f(left, top);
        glVertex3f(x + w, y, z);

        glTexCoord2f(left, bottom);
        glVertex3f(x + w, y - h, z);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);


    // Sprite::draw();
    // Displays bounds of player
    showBounds();

    basket->draw();
    // basket->showBounds();
}

void Player::advance() {
    left += .125;
    right += .125;
    if (right > 1 || !moving) {
        left = 0;
        right = .125;
    }

}

void Player::idle() {
    x += dx;

    if (speedBoost) {
        x += dx;
    }

    if (dx != 0) {
        moving = true;
    } else {
        moving = false;
    }

    if (x < -1) {
        x = -1;
    }
    if (x > 1 - w) {
        x = 1 - w;
    }
    y += dy;
    dy -= .001;
    if (y < -.5) {
        y = -.5;
    }
    if (facingLeft) {
        basket->setX(x - .125);

    } else {
        basket->setX(x + .175);
    }

    basket->setY(y - .1);
}

void Player::jump() {
    dy = .02;
}

void Player::setIsFacingLeft(bool b) {
    facingLeft = b;
}

void Player::setIsFaster(bool b) {
    speedBoost = b;
}

bool Player::isMoving() {
    return moving;
}

bool Player::checkBasketCollision(const Rect &two) {
    return basket->checkCollision(two);
}

bool Player::checkBasketContains(float x, float y) {
    return basket->contains(x, y);
}