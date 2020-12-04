#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "Game.h"


class App: public GlutApp {
    Game* game;
    std::vector<Shape*> shapes;
    int frames;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void idle();
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    void specialKeyUp(int key, float x, float y);

    friend void frameCounter(int id);
    
    ~App();
};

#endif
