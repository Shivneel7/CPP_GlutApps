#include <iostream>
#include "App.h"

static App* singleton;

void timer(int id){
    singleton->cat->advance();
    singleton->redraw();
    if (singleton->cat->isDone()){
        singleton->cat->reset();
    }
    glutTimerFunc(singleton->interval, timer, id);
}

void explosionTimer(int id){
    singleton->explosion->advance();
    singleton->redraw();

    if(singleton->explosion->isDone()){
        singleton->explosionVisible = false;
    }
    glutTimerFunc(17, explosionTimer, id);
}

void platformTimer(int id){
    singleton->platform->setX(singleton->platform->getX() - 0.03);
    singleton->platform2->setX(singleton->platform2->getX() - 0.03);

    if (singleton->platform->getX() < -5){
        singleton->platform->setX(singleton->platform2->getX() + 4);
    }

    if (singleton->platform2->getX() < -5){
        singleton->platform2->setX(singleton->platform->getX() + 4);
    }

    singleton->redraw();
    glutTimerFunc(17, platformTimer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    cat = new Sprite("images/cat.png", 4, 2, -0.5, -0.2, 1, 0.5);
    mushroom = new TexRect("mushroom.png", -0.8, 0.8, 0.5, 0.5);
    bg = new Rect(-1, 1, 2, 2, 0.53, 0.81, 0.92);
    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.5, 0.5);
    platform = new TexRect("platform.jpg", -1, -0.7, 4, 0.3);
    platform2 = new TexRect("platform.jpg", 3, -0.7, 4, 0.3);
    interval = 125;
    shroomVisible = true;
    explosionVisible = false;
    singleton = this;
    timer(1);
    platformTimer(3);
} 

void App::draw() const {
    bg->draw();
    cat->draw(0.5);
    platform->draw();
    platform2->draw();
    if (shroomVisible) {
        mushroom->draw(0.5);
    }
    if (explosionVisible) {
        explosion->draw();
    }

}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    else if(key == ' '){
        shroomVisible = false;
        explosionVisible = true;
        explosionTimer(2);
    }
}


App::~App(){   
    delete cat;
    delete mushroom;
    delete bg;
    delete explosion;
    delete platform;
    std::cout << "Exiting..." << std::endl;
}
