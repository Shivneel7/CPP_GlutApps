#pragma once

#include "MovingTexRect.h"

/**Child of TexRect
 *  Used to display only portions of a .png file that is loaded in a TexRect
 * Includes animation capabilities
 * This is done as I did not want to modify the TexRect file given,
 * however my game needs added functionality which I had to add to a TexRect
 */
class Sprite : public MovingTexRect {
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

    virtual void draw(float z = 0) const;
    virtual void idle();

    bool isDone() const;

    void reset();

    void advance();

    ~Sprite() {
    }
};
