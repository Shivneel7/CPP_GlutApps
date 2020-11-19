#ifndef POINT_H
#define POINT_H

struct Point{
	float x,y;
	int w;

	float r,g,b;

	Point(float x = 2, float y=2, float r=1, float g=0, float b=0,int w=10);

	Point(Point &other);

	void draw();

};

#endif
