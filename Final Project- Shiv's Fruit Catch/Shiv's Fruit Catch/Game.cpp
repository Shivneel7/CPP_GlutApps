#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>

static Game *singleton;
const float Game::PLAYER_BASE_SPEED = .02;

int frames = 0;

void frameCounter(int id) {
    std::cout << "FPS: " << frames << std::endl;
    frames = 0;
    glutTimerFunc(1000, frameCounter, id);
}

void explosionAnimation(int id) {
    singleton->explosion->advance();

    if (!singleton->explosion->isDone()) {
        glutTimerFunc(21, explosionAnimation, id);
    } else {
        singleton->showExplosion = false;
        singleton->explosion->reset();
    }
}

void gameLoop(int id) {
    // Faster Movement controller
    if (singleton->player->isSpeedBoosted() && singleton->player->isMoving()) {
        singleton->hud->decreaseEnergy();

        if (!singleton->hud->hasEnergy()) {
            singleton->player->setSpeedBoost(false);
        }
    }

    for (auto i = singleton->movingGameObjects.begin(); i != singleton->movingGameObjects.end();) {
        bool shouldIncrement = true;
        (*i)->idle();

        switch ((*i)->getID()) {

        case fruit:
            if (singleton->player->checkBasketCollision(*(*i))) {

                singleton->hud->increaseScore(1);

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;

            } else if ((*i)->getY() < -.75) { // Fruit left the screen

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
                // singleton->lost++;
                // singleton->s->setText("Score: " + std::to_string(singleton->score) + " Lost: " + std::to_string(singleton->lost));
            }
            break;

        case health:
            if (singleton->player->checkBasketCollision(*(*i))) {

                singleton->hud->increaseHealth();

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;

            } else if ((*i)->getY() < -.75) { // HealthUpgrade left the screen
                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
            }
            break;

        case energy:
            if (singleton->player->checkBasketCollision(*(*i))) {

                singleton->hud->increaseEnergy();

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
            } else if ((*i)->getY() < -.75) { // Fruit left the screen

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
            }
            break;

        case bomb:
            if (singleton->player->checkCollision(*(*i))) {

                singleton->showExplosion = true;
                explosionAnimation(4);

                singleton->hud->decreaseHealth();
                if (singleton->hud->healthIsEmpty()) {
                    // LOSE
                }

                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;

            } else if ((*i)->getY() < -.7) { // Bomb left the screen
                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
            }
            break;

        case spiny:
            (*i)->advance();

            if ((*i)->getY() < -.65) {
                (*i)->setY(-.65);
                (*i)->setDY(0);
                if ((*i)->getX() < 0) {
                    (*i)->setDX(.01);
                } else {
                    (*i)->setDX(-.01);
                }
            }
            if (singleton->player->checkCollision(*(*i)) && !singleton->player->isInvulnerable()) {
                singleton->player->setInvulnerable(true);

                singleton->hud->decreaseHealth();
                if (singleton->hud->healthIsEmpty()) {
                    // LOSE
                }
            }

            if ((*i)->getX() < -1.2 || (*i)->getX() > 1.2) { // shell left play area
                delete (*i);
                i = singleton->movingGameObjects.erase(i);
                shouldIncrement = false;
            }
            break;
        }

        if (shouldIncrement) {
            ++i;
        }
    }

    singleton->explosion->setX(singleton->player->getX());
    singleton->explosion->setY(singleton->player->getY());

    glutPostRedisplay();
    frames++;

    glutTimerFunc(1000.0 / 60, gameLoop, id);
}

void playerAnimation(int id) {
    singleton->player->advance();
    glutTimerFunc(100, playerAnimation, id);
}

void spawnFruit(int id) {
    singleton->createFruit();
    glutTimerFunc(500, spawnFruit, id);
}

void Game::createFruit() {
    float objectX = (rand() % 190) / 100.0 - 1.0;

    switch (rand() % 8) {
    case 0:
        movingGameObjects.push_back(new Sprite("apple.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 1:
        movingGameObjects.push_back(new Sprite("banana.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 2:
        movingGameObjects.push_back(new Sprite("mango.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 3:
        movingGameObjects.push_back(new Sprite("grape.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 4:
        if (rand() % 2) {
            movingGameObjects.push_back(new Sprite("spiny.png", 1, 16, -1, 1.2, .15, .15, 0, -.01, true, spiny));
        } else {
            movingGameObjects.push_back(new Sprite("spiny.png", 1, 16, .85, 1.2, .15, .15, 0, -.01, true, spiny));
        }
        break;
    case 5:
        movingGameObjects.push_back(new Sprite("bomb.png", objectX, 1.2, .15, .15, 0, -.01, bomb));
        break;
    case 6:
        movingGameObjects.push_back(new Sprite("health.png", objectX, 1.2, .1, .1, 0, -.01, health));
        break;
    case 7:
        movingGameObjects.push_back(new Sprite("energy.png", objectX, 1.2, .1, .1, 0, -.01, energy));
        break;
    }
}

Game::Game() {
    srand(time(NULL));

    showExplosion = false;
    debugModeEnabled = false;
    gameOver = false;

    hud = new HUD();
    bg = new TexRect("bg.png", -1, 1, 2, 2);

    player = new Player(debugModeEnabled);
    movingGameObjects.push_back(player);

    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.3, 0.4, false);

    singleton = this;

    gameLoop(0);

    spawnFruit(1);

    // prints fps of the game every second
    frameCounter(2);

    playerAnimation(3);
    // explosionAnimiation is id = 4
}

void Game::idle() {
}

void Game::keyDown(unsigned char key, float x, float y) {
    if (key == 'a' || key == 'A') {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
        player->setIsFacingLeft(1);

    } else if (key == 'd' || key == 'D') {

        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        player->setIsFacingLeft(0);

    } else if (key == 'w' || key == 'W' || key == ' ') {
        player->jump();
    }
}

void Game::keyUp(unsigned char key, float x, float y) {
    if (key == 'a' || key == 'A') {
        player->setDX(player->getDX() + PLAYER_BASE_SPEED);

    } else if (key == 'd' || key == 'D') {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
    }
}

void Game::specialKeyDown(int key, float x, float y) {
    if (key == GLUT_KEY_SHIFT_L && hud->hasEnergy()) {
        player->setSpeedBoost(true);
    }
}

void Game::specialKeyUp(int key, float x, float y) {
    if (key == GLUT_KEY_SHIFT_L) {
        player->setSpeedBoost(false);
    }
}

void Game::draw() const {
    bg->draw();

    for (auto i = movingGameObjects.begin(); i != movingGameObjects.end(); i++) {
        (*i)->draw();
        if (debugModeEnabled)
            (*i)->showBounds();
    }
    if (showExplosion) {
        explosion->draw();
    }

    hud->draw();
}

Game::~Game() {
    for (auto i = movingGameObjects.begin(); i != movingGameObjects.end(); i++) {
        delete *i;
    }
    delete hud;
    delete explosion;
    delete bg;
}