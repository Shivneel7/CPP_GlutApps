#pragma once

#include "TexRect.h"

/**Bar class, takes 2 pngs. First one is a full bar, second is an empty bar.
The empty bar is displayed on the bottom, and the full bar decreases in size as the value decreases slowly making the bar appear empty
*/
class Bar : public TexRect {
  protected:
    TexRect *base;

    float percent;

  public:
    Bar(const char *filename, float x, float y, float w, float h, const char *empty, bool startWithFullBar);
    virtual void draw(float z) const;

    void increment(float f);
    float getPercent() const;

    bool isEmpty();
};