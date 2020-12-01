#include <iostream>
#include "App.h"

static App* singleton;


void frameCounter(int id){
    std::cout << "FPS: " << singleton->frames << std::endl;
    singleton->frames = 0;
    glutTimerFunc(1000, frameCounter, 0);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    game = new Game();
    frames = 0;
    singleton = this;
    frameCounter(0);
} 



void App::draw() const {
    game->draw();
}

void App::idle(){
    game->idle();
    redraw();
    frames++;
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
