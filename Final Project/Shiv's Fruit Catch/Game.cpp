#include "Game.h"
#include <iostream>

static Game *singleton;

void explosionTimer(int id) {
    singleton->explosion->advance();
    glutTimerFunc(33, explosionTimer, id);
}

void timer(int id) {
    singleton->player->idle();
    glutTimerFunc(1000.0 / 60.0, timer, id);
}

Game::Game() {

    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.25, 0.25);
    player = new Player();
    shapes.push_back(player);

    // Pushing different kinds of Shape in the collection
    shapes.push_back(explosion);
    shapes.push_back(new Text(0, 0, "this is some text", 0, 0, 1));
    singleton = this;
    timer(1);

    explosionTimer(0);
}

void Game::idle() {
    // player->idle();
}

void Game::keyDown(unsigned char key, float x, float y) {
    if (key == ' ') {
    }
}

void Game::keyUp(unsigned char key, float x, float y) {
}

void Game::specialKeyDown(int key, float x, float y) {
    if (key == GLUT_KEY_LEFT) {
        player->setDX(player->getDX() - player->getSpeed());
        player->setDirection(1);
    } else if (key == GLUT_KEY_RIGHT) {
        player->setDX(player->getDX() + player->getSpeed());
        player->setDirection(0);

    } else if (key == GLUT_KEY_UP) {
        player->jump();
    }
}

void Game::specialKeyUp(int key, float x, float y) {
    if (key == GLUT_KEY_LEFT) {
        player->setDX(player->getDX() + player->getSpeed());

    } else if (key == GLUT_KEY_RIGHT) {
        player->setDX(player->getDX() - player->getSpeed());
    } else if (key == GLUT_KEY_DOWN) {
        // player->setSpeed();
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