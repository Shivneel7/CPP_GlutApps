#ifndef HANDLER_H
#define HANDLER_H

#include "Rect.h"
#include <deque>


struct Handler {
	std::deque<Rect*> rects;

	//offset of mx from left side of rectangle. used for dragging
	float xO;
	//offset of mY from the top side of rectangle. used for dragging
	float yO;

	//how much leeway user has to grab the bottom right corner for resizing. Higher values = more freedom to grab
	float grabLeeway;

	//Set random to true to allow random colors.
	Handler(int numRects, bool random);

	void draw();

	void mouseFunc(float mx, float my, int s);

	void drag(float mx, float my);

	int negOrPos();

	float xBounds(float x, float w);
	float yBounds(float y, float h);

};


#endif
