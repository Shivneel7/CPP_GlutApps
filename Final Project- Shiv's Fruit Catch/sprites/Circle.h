#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle: public Shape{
	float x;
	float y;

	float radius;

	float r;
	float g;
	float b;

public:
	Circle();
	Circle(float, float, float);

	void draw(float z = 0) const;

	void setY(float);
	float getY() const;
};


#endif
