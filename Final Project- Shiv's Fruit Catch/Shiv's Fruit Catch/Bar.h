#pragma once

#include "TexRect.h"

class Bar : TexRect {
  protected:
    float right;

  public:
    Bar(const char *filename, float x, float y, float w, float h);
    virtual void draw(float z) const;

    void setRight(float);
};