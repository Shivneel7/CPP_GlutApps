#include <iostream>
#include "App.h"

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    game = new Game(width,height);
}

void App::draw() {
    game->draw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }

    game->keyDown(key,x,y);
}

void App::keyUp(unsigned char key, float x, float y){
    game->keyUp(key,x,y);

}

void App::idle() {
    game->idle();
    redraw();

}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete game;
}
