#ifndef RECT_H
#define RECT_H

#include "Shape.h"

class Rect: public Shape{
protected:
	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float b;

public:
	Rect();
	Rect(float, float, float, float, float r=1, float g=0, float b=0);

	virtual void draw(float z=0) const;
    virtual bool checkCollision(const Rect &r) const;

	void setY(float y);
	float getY() const;
	float getX() const;
	void setX(float x);
	void setW(float);
	float getW() const;
	float getH() const;
	void setH(float);
	void setColor(float r, float g, float b);

	bool contains(float, float) const;
};

#endif
