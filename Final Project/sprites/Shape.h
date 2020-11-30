#pragma once

class Shape{
public:
	virtual void draw(float zindex = 0) const = 0;
	
	virtual ~Shape() {}
};
