#include "Player.h"

Player::Player() : MovingTexRect("player-idle.png", -.1, -.72, .3, .3, 0, 0, .01), direction(0), BASE_SPEED(.01){
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

void Player::jump() {
}

void Player::setDirection(bool b){
    direction = b;
}