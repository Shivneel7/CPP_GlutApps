#include "Game.h"
#include <iostream>

static Game *singleton;


void explosionTimer(int id) {
    singleton->explosion->advance();
    glutTimerFunc(33, explosionTimer, id);
}

// void timer(int){
//     std::cout << "test" << std::endl;
//     glutTimerFunc(1000, timer, 0);
// }

Game::Game() {

    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.25, 0.25);
    player = new TexRect("player-idle.png", -.1, -.72, .3, .3);
    shapes.push_back(player);

    // Pushing different kinds of Shape in the collection
    shapes.push_back(explosion);
    shapes.push_back(new Text(0,0, "this is some text", 0, 0, 1));
    singleton = this;
    // glutTimerFunc(1000, timer, 1);

    explosionTimer(0);
}



void Game::keyDown(unsigned char key, float x, float y) {
    if(key == ' '){

    }
}

void Game::specialKeyDown(int key, float x, float y) {
    if(key == GLUT_KEY_LEFT){
        player->setX(player->getX() -.05);
    }else if(key == GLUT_KEY_RIGHT){
        player->setX(player->getX() +.05);
    }else if(key == GLUT_KEY_UP){

    }
}

void Game::draw() const {
    for (auto i = shapes.begin(); i != shapes.end(); i++) {
        (*i)->draw();
    }
}

Game::~Game() {
    for (auto i = shapes.begin(); i != shapes.end(); i++) {
        delete *i;
    }
}