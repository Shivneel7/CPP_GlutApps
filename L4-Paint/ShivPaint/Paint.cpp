#include "Paint.h"

Paint::Paint(int w, int h): w(w),h(h){
    eraser = false;
    brushWidth = 10;
    r = 0;
    g = 0;
    b = 0;
    
    Button* brush = new Button(-.99,.98,.17,.06,0,1,0,"Brush", .01, 0,true);
	Button* eraser = new Button(-.99,.91,.17,.06,1,0,0,"Eraser", .005,0,true);

	Button* sizeText = new Button(-.99,.82,.17,.06,1,1,1,"Sizes", 0,0,true);

	Button* size1 = new Button(-.98,.74,.025,.025,0,0,0,"s1", 0,0);
	Button* size2 = new Button(-.89,.75,.035,.035,0,0,0,"s2", 0,0);
	Button* size3 = new Button(-.99,.65,.045,.045,0,0,0,"s3", 0,0);
	Button* size4 = new Button(-.9,.65,.055,.055,0,0,0,"s4", 0,0);

    float colorX = -.97, colorXOffset = .07;
    
	Button* colorText = new Button(-.99,.55,.17,.06,1,1,1,"Colors", 0,0,true);

	Button* color1 = new Button(colorX,                 .5,.05,.05, 0, 0, 0,"c", 0,0);
	Button* color2 = new Button(colorX + colorXOffset,  .5,.05,.05, .5, .5, .5,"c", 0,0);
	Button* color3 = new Button(colorX,                 .44,.05,.05, 1, 0, 0,"c", 0,0);
	Button* color4 = new Button(colorX + colorXOffset,  .44,.05,.05, 1, 1, 0,"c", 0,0);
	Button* color5 = new Button(colorX,                 .38,.05,.05, 0, 1, 0,"c", 0,0);
	Button* color6 = new Button(colorX + colorXOffset,  .38,.05,.05, 0, 1, 1,"c", 0,0);
	Button* color7 = new Button(colorX,                 .32,.05,.05, 0, 0, 1,"c", 0,0);
	Button* color8 = new Button(colorX + colorXOffset,  .32,.05,.05, 75.0/255, 0, 130.0/255,"c", 0,0);

    Button* clear = new Button(-.99,.25,.17,.06,1,0,0,"Clear", .01, 0,true);
    
    Button* GUIBound = new Button(-1,1,.2,.83,1,1,1,"GUI", 0, 0);

    buttons.push_back(brush);
    buttons.push_back(eraser);
    buttons.push_back(sizeText);

    buttons.push_back(size1);
    buttons.push_back(size2);
    buttons.push_back(size3);
    buttons.push_back(size4);

    buttons.push_back(colorText);
    buttons.push_back(color1);
    buttons.push_back(color2);
    buttons.push_back(color3);
    buttons.push_back(color4);
    buttons.push_back(color5);
    buttons.push_back(color6);
    buttons.push_back(color7);
    buttons.push_back(color8);

    buttons.push_back(clear);

    buttons.push_back(GUIBound);


}

Paint::Paint(const Paint &other):w(other.w),h(other.h), eraser(other.eraser), brushWidth(other.brushWidth), r(other.r), g(other.g), b(other.b){
    for(Point* p: other.points){
        points.push_back(new Point(*p));
    }
    for(Button* b: other.buttons){
        buttons.push_back(new Button(*b));
    }
}

void Paint::draw(){
    for(Button* b:buttons){
        b->draw(w,h);
    }
    for(Point* p:points){
        p->draw();
    }
}

void Paint::mouseClick(float mx, float my, int s){
    //buttons:
    if(!s){
        for(Button* b : buttons){
            if(b->contains(mx,my)){
                if(b->text == "Brush"){
                    b->changeColor(0,1,0);
                    buttons[1]->changeColor(1,0,0);
                    eraser = false;
                    return;
                }
                if(b->text == "Eraser"){
                    b->changeColor(0,1,0);
                    buttons[0]->changeColor(1,0,0);
                    eraser = true;
                    return;
                }
                //sizes
                if(b->text == "s1"){
                    brushWidth = 5;
                }
                if(b->text == "s2"){
                    brushWidth = 10;
                }
                if(b->text == "s3"){
                    brushWidth = 16;
                }
                if(b->text == "s4"){
                    brushWidth = 22;
                }
                //color
                if(b->text == "c"){
                    this->r = b->r;
                    this->g = b->g;
                    this->b = b->b;
                    return;
                }
                //clear
                if(b->text == "Clear"){
                    clearCanvas();
                    eraser = false;
                    buttons[0]->changeColor(0,1,0);
                    buttons[1]->changeColor(1,0,0);
                    return;
                }
            }
        }
    }

    //Drawing
    if (eraser){
		points.push_front(new Point(mx, my, 1, 1, 1,brushWidth));
	}
	else{
		points.push_front(new Point(mx, my, r, g, b,brushWidth));
	}
}

void Paint::drag(float mx, float my){
    if (eraser){
		points.push_front(new Point(mx, my, 1,1,1,brushWidth));
	}
	else{
		points.push_front(new Point(mx, my, r, g, b, brushWidth));
	}
}

void Paint::clearCanvas(){
    for(Point* p: points){
        delete p;
    }
    points.clear();
}

