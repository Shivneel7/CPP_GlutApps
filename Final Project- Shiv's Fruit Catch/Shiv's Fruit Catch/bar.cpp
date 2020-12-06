#include "Bar.h"

// have a texture, the "right" attribute depletes with time.

Bar::Bar(const char *filename, float x, float y, float w, float h, const char *empty, bool startWithFullBar) : TexRect(filename, x, y, w, h), base(new TexRect(empty, x, y, w, h)) {
    percent = startWithFullBar;
}

void Bar::draw(float z) const {
    base->draw(z);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x, y - h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(percent, 1);
    glVertex3f(x + w - (1 - percent) * w, y, z);

    glTexCoord2f(percent, 0);
    glVertex3f(x + w - (1 - percent) * w, y - h, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Bar::increment(float f) {
    percent += f;
    if (percent > 1) { // since I use floats, set the value to exact 1
        percent = 1;
    }
    if (percent < 0) { // since I use floats, set the value to exact 0
        percent = 0;
    }
}

float Bar::getPercent() const {
    return percent;
}
