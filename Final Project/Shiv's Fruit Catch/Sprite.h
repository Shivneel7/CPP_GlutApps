#pragma once

#include "TexRect.h"

class Sprite : public TexRect {
  protected:
    int rows;
    int cols;

    float xinc;
    float yinc;

    int curr_row;
    int curr_col;

    float left;
    float right;
    float top;
    float bottom;

    bool done;

  public:
    Sprite(const char *filename, int rows, int cols, float x, float y, float w, float h);

    // Sprite(const char *filename, int rows, int cols, float l, float r, float x, float y, float w, float h);

    virtual void draw(float z = 0) const;

    bool isDone() const;

    void reset();

    void advance();

    ~Sprite() {
    }
};
