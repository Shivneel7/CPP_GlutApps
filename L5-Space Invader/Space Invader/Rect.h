#ifndef RECT_H
#define RECT_H


class Rect {
protected:	
	float x;
	float y;

	float red;
	float green;
	float blue;

	float w;
	float h;

public:
	Rect();

	Rect(float, float, float, float);

	Rect(float, float, float, float, float, float, float);

	Rect(const Rect&);

	bool operator== (const Rect&);

	~Rect();

	void draw();

	bool contains(float, float) const;

	float getX() const ;

	float getY() const ;

	float getW() const ;

	float getH() const ;

	float getR() const ;

	float getG() const ;

	float getB() const ;

	void setX(float x);

	void setY(float y);

	void setW(float w);

	void setH(float h);

};




#endif
