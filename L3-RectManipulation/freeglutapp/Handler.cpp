#include "Handler.h"
#include <math.h>
#include <time.h>
#include <iostream>

//@param: random: set to true for random colors
//numRects works best if random is set to true. Otherwise same 5 colors will be repeated
Handler::Handler(int numRects, bool random){
	srand (time(NULL));
	// rects.push_back(new Rect(((rand()%70)/100.0) * negOrPos(),((rand()%70)/100.0) * negOrPos(), (rand()%40 + 30)/100.0, (rand()%40 + 20)/100.0, 0, 1, 0, 0));
	// rects.push_back(new Rect(((rand()%70)/100.0) * negOrPos(),((rand()%70)/100.0) * negOrPos(), (rand()%40 + 30)/100.0, (rand()%40 + 20)/100.0, 1, 0, 0, 0));
	// rects.push_back(new Rect(((rand()%70)/100.0) * negOrPos(),((rand()%70)/100.0) * negOrPos(), (rand()%40 + 30)/100.0, (rand()%40 + 20)/100.0, 0, 0, 1, 0));
	// rects.push_back(new Rect(((rand()%70)/100.0) * negOrPos(),((rand()%70)/100.0) * negOrPos(), (rand()%40 + 30)/100.0, (rand()%40 + 20)/100.0, 1, 1, 0, 0));
	// rects.push_back(new Rect(((rand()%70)/100.0) * negOrPos(),((rand()%70)/100.0) * negOrPos(), (rand()%40 + 30)/100.0, (rand()%40 + 20)/100.0, 0, 1, 1, 0));
	// rects.push_back(new Rect(0,0,.5,.5,0,0,1,0));

	for(int i = 0; i < numRects; i++){
		float w = (rand()%30 + 40)/100.0;
		float h = (rand()%30 + 40)/100.0;
		float x = xBounds(((rand()%90)/100.0) * negOrPos(),w);
		float y = yBounds(((rand()%90)/100.0) * negOrPos(),h);

		if(!random){
			if(i%5==0)
				rects.push_back(new Rect(x, y, w, h,1,0,0,i));
			if(i%5==1)
				rects.push_back(new Rect(x, y, w, h,0,1,0,i));
			if(i%5==2)
				rects.push_back(new Rect(x, y, w, h,0,0,1,i));
			if(i%5==3)
				rects.push_back(new Rect(x, y, w, h,0,1,1,i));
			if(i%5==4)
				rects.push_back(new Rect(x, y, w, h,1,1,0,i));
		}

		//random colors
		if(random)
			rects.push_back(new Rect(x, y, w, h,rand()%256/255.0,rand()%256/255.0,rand()%256/255.0,i));

	}
}

void Handler::draw(){
	for(Rect* r : rects){
		r->draw();
	}
}

void Handler::mouseFunc(float mx, float my, int s){
	//if we lift the mouse button, stop resizing.
	if(s)
		for(Rect* r : rects)
			r->resizing=false;
	
	if (!s){
		for(auto r = rects.begin(); r != rects.end(); r ++){
			if((*r)->contains(mx,my)){

				(*r)->select();
				xO = mx - (*r)->x;
				yO = (*r)->y - my;

				//change this to edit how small the area we have to click to begin resizing is
				grabLeeway = .0135; 

				if(xO > (*r)->w-grabLeeway && xO < (*r)->w+grabLeeway && yO > (*r)->h-grabLeeway && yO < (*r)->h+grabLeeway){
					(*r)->resizing = true;
				}
	
				//Without the temp variable, the rectangle sometimes gets erased if you have more than 2 rectangles.
				Rect* temp = *r;

				rects.erase(r);

				rects.push_front(temp);

				break;
			}else
				(*r)->deselect();
		}
	}		
}

void Handler::drag(float mx, float my){
	for(auto r = rects.begin(); r != rects.end(); r ++){
		if((*r)->selected){
			//Resize if user clicked bottom right corner
			if((*r)->resizing){
				//stops user from making rectangles with negative width
				if((mx - (*r)->x) > grabLeeway){
					(*r)->w = mx - (*r)->x;
				}
				//stops user from making rectangles with negative height
				if(-my + (*r)->y > grabLeeway){
					(*r)->h = -my + (*r)->y;
				}

				//used the line of code below to pick a good grabLeeway. it displays width and height as user resizes
				//std::cout << "w: " <<(*r)->w << " h: "<<(*r)->h<<  std::endl;
			}else{
				//Dragging
				(*r)->x = mx - xO;
				(*r)->y = my + yO;
			}
		}
	}
}

//@returns -1 or 1
int Handler::negOrPos(){
	if(rand()%2)
		return 1;
	return -1;
}

//@return an x coordinate such that the whole rectangle is displayed on the screen
float Handler::xBounds(float x, float w){
	if(x + w > 1){
		return .99-w;
	}
	return x;
}

//@return a y coordinate such that the whole rectangle is displayed on the screen
float Handler::yBounds(float y, float h){
	if(y - h < -1){
		return -.99+h;
	}
	return y;
}