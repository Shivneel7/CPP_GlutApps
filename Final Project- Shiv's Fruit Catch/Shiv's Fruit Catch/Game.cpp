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
    for (auto i = singleton->objects.begin(); i != singleton->objects.end();) {
        bool shouldIncrement = true;
        (*i)->idle();

        if ((*i)->getID() == fruit) {

            if (singleton->player->checkBasketCollision(*(*i))) {

                singleton->hud->increaseScore();

                delete (*i);
                i = singleton->objects.erase(i);
                shouldIncrement = false;

            } else if ((*i)->getY() < -.75) { // Fruit left the screen

                delete (*i);
                i = singleton->objects.erase(i);
                shouldIncrement = false;
                // singleton->lost++;
                // singleton->s->setText("Score: " + std::to_string(singleton->score) + " Lost: " + std::to_string(singleton->lost));
            }
        }

        if ((*i)->getID() == bomb) {
            if (singleton->player->checkCollision(*(*i))) {

                singleton->showExplosion = true;
                explosionAnimation(4);

                singleton->hud->decreaseHealth();
                std::cout << "Lose Health" << std::endl;

                delete (*i);
                i = singleton->objects.erase(i);
                shouldIncrement = false;

            } else if ((*i)->getY() < -.7) { // Bomb left the screen
                delete (*i);
                i = singleton->objects.erase(i);
                shouldIncrement = false;
            }
        }

        if ((*i)->getID() == spiny) {
            (*i)->advance();
            if ((*i)->getY() < -.65) {
                (*i)->setY(-.65);
                (*i)->setDY(0);
                (*i)->setDX(.01);
            }
            if (singleton->player->checkCollision(*(*i)) && !singleton->player->isInvulnerable()) {
                singleton->player->setInvulnerable(true);

                std::cout << "Lose Health" << std::endl;
                singleton->hud->decreaseHealth();
            }

            if ((*i)->getX() < -1.2 || (*i)->getX() > 1.2) { // shell left play area
                delete (*i);
                i = singleton->objects.erase(i);
                shouldIncrement = false;
            }
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
    float fruitX = (rand() % 190) / 100.0 - 1.0;

    switch (rand() % 6) {
    case 0:
        objects.push_back(new Sprite("apple.png", fruitX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 1:
        objects.push_back(new Sprite("banana.png", fruitX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 2:
        objects.push_back(new Sprite("mango.png", fruitX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 3:
        objects.push_back(new Sprite("grape.png", fruitX, 1.2, .1, .1, 0, -.01, fruit));
        break;
    case 4:
        objects.push_back(new Sprite("spiny.png", 1, 16, -1, 1.2, .15, .15, 0, -.01, true, spiny));
        break;
    case 5:
        objects.push_back(new Sprite("bomb.png", fruitX, 1.2, .15, .15, 0, -.01, bomb));
    }
}

Game::Game() {
    srand(time(NULL));

    showExplosion = false;
    debugModeEnabled = false;

    hud = new HUD();

    lost = 0;

    player = new Player(debugModeEnabled);
    objects.push_back(player);

    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.3, 0.4, false);

    bg = new TexRect("bg.png", -1, 1, 2, 2);
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

    } else if (key == 'w' || key == 'W') {
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
    if (key == GLUT_KEY_SHIFT_L) {
        player->setIsFaster(true);
    }
}

void Game::specialKeyUp(int key, float x, float y) {
    if (key == GLUT_KEY_SHIFT_L) {
        player->setIsFaster(false);
    }
}

void Game::draw() const {
    bg->draw();

    for (auto i = objects.begin(); i != objects.end(); i++) {
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
    for (auto i = objects.begin(); i != objects.end(); i++) {
        delete *i;
    }
    delete hud;
    delete explosion;
    delete bg;
}