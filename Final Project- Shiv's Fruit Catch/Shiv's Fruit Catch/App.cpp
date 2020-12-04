#include <iostream>
#include "App.h"

static App* singleton;

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    //when a key is pressed, the key only triggers one event
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    game = new Game();
    frames = 0;
    singleton = this;
} 

void App::draw() const {
    game->draw();
}

void App::idle(){
    game->idle();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    game->keyDown(key, x, y);
}

void App::specialKeyDown(int key, float x, float y){
    game->specialKeyDown(key, x, y);
}

void App::keyUp(unsigned char key, float x, float y){
    game->keyUp(key, x, y);
}

void App::specialKeyUp(int key, float x, float y){
    game->specialKeyUp(key, x, y);
}

App::~App(){
    delete game;
    std::cout << "Exiting..." << std::endl;
}
