#include "Player.h"
#include "iostream"

Player::Player() : MovingSprite("player-idle.png", 1, 1, -.1, -.72, .3, .3, 0, 0, player), direction(0){
}

void Player::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);

    if (!direction) {
        glTexCoord2f(1, 0);
        glVertex3f(x, y - h, z);

        glTexCoord2f(1, 1);
        glVertex3f(x, y, z);

        glTexCoord2f(0, 1);
        glVertex3f(x + w, y, z);

        glTexCoord2f(0, 0);
        glVertex3f(x + w, y - h, z);
    } else {
        glTexCoord2f(0, 0);
        glVertex3f(x, y - h, z);

        glTexCoord2f(0, 1);
        glVertex3f(x, y, z);

        glTexCoord2f(1, 1);
        glVertex3f(x + w, y, z);

        glTexCoord2f(1, 0);
        glVertex3f(x + w, y - h, z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Player::idle() {
    x += dx;
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
