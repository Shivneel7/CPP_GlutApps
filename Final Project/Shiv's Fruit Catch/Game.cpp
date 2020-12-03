#include "Game.h"
#include <iostream>
#include <string>

static Game *singleton;
const float Game::PLAYER_BASE_SPEED = .01;

int frames = 0;

void frameCounter(int id) {
    std::cout << "FPS: " << frames << std::endl;
    frames = 0;
    glutTimerFunc(1000, frameCounter, id);
}

void gameLoop(int id) {
    singleton->player->idle();
    // singleton->explosion->setX(singleton->player->getX());
    // singleton->explosion->advance();

    for (auto i = singleton->objects.begin(); i != singleton->objects.end(); i++) {
        (*i)->idle();
        if (singleton->player->contains((*i)->getX(), (*i)->getY())) {
            singleton->score++;
            singleton->s->setText("Score: " + std::to_string(singleton->score));
            delete (*i);
            singleton->objects.erase(i);
        }
    }
    glutPostRedisplay();
    frames++;

    // std::cout << singleton->score << std::endl;

    glutTimerFunc(1000.0 / 60, gameLoop, id);
}


void spawnBanana(int id) {
    singleton->objects.push_back(new Fruit());
    // singleton->objects.push_back(new MovingSprite("banana.png", 1, 1, 0, 1, .1, .1, 0, -.01, fruit));
    // singleton->test = new TexRect("banana.png");
    glutTimerFunc(1000, spawnBanana, id);
}
Game::Game() {
    score = 0;
    // explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.25, 0.25);
    player = new Player();

    // shapes.push_back(player);

    // objects.push_back(new Fruit());
    // objects.push_back(new Fruit());
    // objects.push_back(new Fruit());

    s = new Text(0, 0, "score: 0", 0, 0, 1);

    // Pushing different kinds of Shape in the collection
    // shapes.push_back(explosion);
    // shapes.push_back(new Text(0, 0, "this is some text", 0, 0, 1));
    singleton = this;

    gameLoop(0);
    spawnBanana(2);
    // prints fps of the game every second
    frameCounter(1);
}

void Game::idle() {
    
}

void Game::keyDown(unsigned char key, float x, float y) {
    if (key == ' ') {
    }
}

void Game::keyUp(unsigned char key, float x, float y) {
}

void Game::specialKeyDown(int key, float x, float y) {
    if (key == GLUT_KEY_LEFT) {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
        player->setDirection(1);
        // std::cout<< (rand()%190)/100.0 - 1.0<< std::endl;

    } else if (key == GLUT_KEY_RIGHT) {

        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        player->setDirection(0);

    } else if (key == GLUT_KEY_UP) {
        player->jump();
    }
}

void Game::specialKeyUp(int key, float x, float y) {
    if (key == GLUT_KEY_LEFT) {
        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        // std::cout << player->getDX() << std::endl;

    } else if (key == GLUT_KEY_RIGHT) {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);

    } else if (key == GLUT_KEY_DOWN) {
        // player->setSpeed();
    }
}

void Game::draw() const {
    player->draw();
    s->draw(1);
    for (auto i = objects.begin(); i != objects.end(); i++) {
        (*i)->draw();
    }
    for (auto i = hud.begin(); i != hud.end(); i++) {
        (*i)->draw();
    }
}

Game::~Game() {
    for (auto i = objects.begin(); i != objects.end(); i++) {
        delete *i;
    }
    for (auto i = hud.begin(); i != hud.end(); i++) {
        delete *i;
    }
    delete player;
}