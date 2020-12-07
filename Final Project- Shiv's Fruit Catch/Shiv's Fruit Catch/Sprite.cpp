#include "Sprite.h"

Sprite::Sprite(const char *filename, float x, float y, float w, float h, ID id) : MovingTexRect(filename, x, y, w, h, dx, dy, id) {
    rows = 1;
    cols = 1;

    reset();
}

Sprite::Sprite(const char *filename, float x, float y, float w, float h, float dx, float dy, ID id) : MovingTexRect(filename, x, y, w, h, dx, dy, id) {
    rows = 1;
    cols = 1;

    reset();
}

Sprite::Sprite(const char *filename, int rows, int cols, float x, float y, float w, float h, bool l, ID id) : MovingTexRect(filename, x, y, w, h, 0, 0, id) {
    this->rows = rows;
    this->cols = cols;
    this->loop = l;

    reset();
}

Sprite::Sprite(const char *filename, int rows, int cols, float x, float y, float w, float h, float dx, float dy, bool l, ID id) : MovingTexRect(filename, x, y, w, h, dx, dy, id) {
    this->rows = rows;
    this->cols = cols;
    this->loop = l;

    reset();
}

bool Sprite::isDone() const {
    return done;
}

void Sprite::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(left, bottom);
    glVertex3f(x, y - h, z);

    glTexCoord2f(left, top);
    glVertex3f(x, y, z);

    glTexCoord2f(right, top);
    glVertex3f(x + w, y, z);

    glTexCoord2f(right, bottom);
    glVertex3f(x + w, y - h, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Sprite::reset() {
    xinc = 1.0 / cols;
    yinc = 1.0 / rows;
    done = false;
    left = 0;
    right = xinc;
    bottom = 1 - yinc;
    top = 1;
}

void Sprite::advance() {
    left += xinc;
    right += xinc;

    if (right > 1) {
        left = 0;
        right = xinc;
        bottom -= yinc;
        top -= yinc;

        if (bottom < 0) {
            done = true;
            if (loop) {
                reset();
            }
        }
    }
}
