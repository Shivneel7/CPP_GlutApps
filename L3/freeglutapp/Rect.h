#ifndef RECT_H
#define RECT_H


struct Rect {
	float x;
	float y;
	
	float w;
	float h;

	float red;
	float green; 
	float blue;

	bool selected;
	bool resizing;
	int num; // for debugging purposes

	Rect(); // This is a default constructor (takes no parameters)

	Rect(float x, float y, float w, float h, float red, float green, float blue, int num);

	void draw();

	bool contains(float x, float y);

	void select();
	void deselect();
};

#endif
