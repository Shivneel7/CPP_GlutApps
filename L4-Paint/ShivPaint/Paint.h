#ifndef PAINT_H
#define PAINT_H

#include <deque>
#include "Point.h"
#include "Button.h"

struct Paint{
    std::deque<Point*> points;
    std::deque<Button*> buttons;
    
    int w, h, brushWidth;
    bool eraser;
    float r,g,b;

    Paint(int w = 640, int h = 480);
    Paint(const Paint &p);

    void draw();

    void mouseClick(float mx, float my, int s);
    void drag(float mx, float my);

    void clearCanvas();
};

#endif
