#ifndef RECT_H
#define RECT_H


struct Rect {
	float x;
	float y;

	char mark;

	float red;
	float green; 
	float blue;

	float w;
	float h;

	Rect(); // This is a default constructor (takes no parameters)

	Rect(float x, float y, float w, float h, char mark);

	Rect(float x, float y, float w, float h, float red, float green, float blue, char mark);

	void draw();
	
	bool contains(float mx, float my);

	void select(char mark);

	bool isBlank();
	
};




#endif
