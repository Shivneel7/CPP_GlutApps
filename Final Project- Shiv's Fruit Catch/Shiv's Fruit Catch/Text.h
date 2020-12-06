#pragma once

// #include "Shape.h"
#include "Rect.h"
#include <string>

/**A rectangle that displays a string of text
 */
class Text : public Rect {
  protected:
    std::string text;
    int windowW, windowH;
    void *font;
    bool showRectangle;

  public:
    Text();

    Text(float, float, std::string);

    Text(float, float, std::string, float, float, float);

    Text(Text &other);

    void draw(float z = 0) const;

    void setText(std::string t);

    void setFont(void *font);
};