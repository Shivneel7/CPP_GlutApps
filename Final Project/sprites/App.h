#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "Rect.h"
#include "Circle.h"
#include "TexRect.h"
#include "Sprite.h"

class App: public GlutApp {

    Sprite* cat;
    Sprite* explosion;
    TexRect* mushroom;
    Rect* bg;
    TexRect* platform;
    TexRect* platform2;
    unsigned int interval;
    bool shroomVisible;
    bool explosionVisible;

public:
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);

    friend void timer(int id);

    friend void explosionTimer(int id);

    friend void platformTimer(int id);
    
    ~App();
};

#endif
