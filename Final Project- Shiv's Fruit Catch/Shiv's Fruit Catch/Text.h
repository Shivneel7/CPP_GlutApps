#pragma once

// #include "Shape.h"
#include "Rect.h"
#include <string>

/**A rectangle that displays a string of text
 */
class Text : public Rect {
    std::string text;
    int windowW, windowH;
    void *font;

  public:
    Text(float, float, std::string, float, float, float);

    void draw(float z = 1) const;

    void setText(std::string t);

};