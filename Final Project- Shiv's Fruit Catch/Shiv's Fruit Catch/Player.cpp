#include "Player.h"
#include "iostream"

Player::Player() : Sprite("player.png", 1, 8, -.1, -.62, .25, .3, 0, 0, true, player), facingLeft(0), speedBoost(0), basket(new MovingTexRect("basket1.png", -.1, -.72, .2, .1, 0, 0, defaultID)), jumping(false), invulnerable(0), showPlayer(true), invulnerableCount(0) {
}

void Player::draw(float z) const {
    if (showPlayer) {
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
    left += xinc;
    right += xinc;
    if (right > 1 || !moving) {
        left = 0;
        right = xinc;
    }
}

void Player::idle() {
    MovingTexRect::idle();

    if (invulnerable) {
        showPlayer = !showPlayer;
        invulnerableCount++;
    }
    if (invulnerableCount > 100) {
        invulnerable = false;
        invulnerableCount = 0;
        showPlayer = true;
    }

    if (speedBoost) {
        x += dx;
    }

    // used for animation
    if (dx != 0) {
        moving = true;
    } else {
        moving = false;
    }

    // so the player does not leave the play area
    if (x < -1) {
        x = -1;
    }

    if (x > 1 - w) {
        x = 1 - w;
    }

    // gravity
    dy -= .001;

    if (y < -.5) {
        jumping = false;
        y = -.5;
        dy = 0;
    }

    // Keep basket equipped
    if (facingLeft) {
        basket->setX(x - .125);

    } else {
        basket->setX(x + .175);
    }
    basket->setY(y - .1);
}

void Player::jump() {
    if (!jumping) {
        dy = .02;
        jumping = true;
    }
}

void Player::setIsFacingLeft(bool b) {
    facingLeft = b;
}

void Player::setIsFaster(bool b) {
    speedBoost = b;
}

bool Player::isMoving() const {
    return moving;
}

void Player::setInvulnerable(bool b) {
    invulnerable = b;
}

bool Player::isInvulnerable() const {
    return invulnerable;
}

bool Player::checkBasketCollision(const Rect &two) {
    return basket->checkCollision(two);
}

bool Player::checkBasketContains(float x, float y) {
    return basket->contains(x, y);
}