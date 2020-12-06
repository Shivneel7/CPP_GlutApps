#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>

static Game *singleton;
const float Game::PLAYER_BASE_SPEED = .02;

int frames = 0;

void frameCounter(int id) {
    if (!singleton->debugModeEnabled) {
        std::cout << "FPS: " << frames << std::endl;
    } else {
        std::cout << "Seconds " << singleton->seconds << std::endl;
    }

    frames = 0;
    if (!singleton->paused && !singleton->gameOver && !singleton->preGame) {
        singleton->seconds++;
        if (singleton->seconds % Game::DIFFICULTY_INCREASE_MODIFIER == 0) {
            singleton->difficulty++;
            std::cout << "Difficulty " << singleton->difficulty << std::endl;
        }
    }
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
    if (singleton->preGame) {
        singleton->demo->advance();
    }

    if (!singleton->paused && !singleton->gameOver) {

        // Faster Movement controller
        if (singleton->player->isSpeedBoosted() && singleton->player->isMoving()) {
            if (!singleton->preGame) {
                singleton->hud->decreaseEnergy();
            }

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
                    singleton->hud->droppedFruit();
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
                } else if ((*i)->getY() < -.75) { // Energy left the screen

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
                        singleton->hud->setSeconds(singleton->seconds);
                        singleton->gameOver = true;
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
                if (singleton->player->checkCollision(*(*i)) && !singleton->player->isInvulnerable()) {
                    singleton->player->setInvulnerable(true);

                    singleton->hud->decreaseHealth();
                    if (singleton->hud->healthIsEmpty()) {
                        singleton->hud->setSeconds(singleton->seconds);
                        singleton->gameOver = true;
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
    }
    glutTimerFunc(1000.0 / 60, gameLoop, id);
}

void playerAnimation(int id) {
    if (!singleton->paused && !singleton->gameOver)
        singleton->player->advance();

    glutTimerFunc(100, playerAnimation, id);
}

void spawnFallingObjectLoop(int id) {
    if (!singleton->paused && !singleton->gameOver && !singleton->preGame)
        singleton->spawnFallingObject();

    glutTimerFunc(500, spawnFallingObjectLoop, id);
}

Game::Game() {
    srand(time(NULL));
    debugModeEnabled = 0;
    preGame = true;
    paused = false;
    gameOver = false;
    difficulty = 0;
    seconds = 0;
    showExplosion = false;

    hud = new HUD();

    infoScreen = new TexRect("info.png", -1, 1, 2, 2);

    bg = new TexRect("bg.png", -1, 1, 2, 2);
    pauseScreen = new TexRect("pause.png", -1, 1, 2, 2);
    lossScreen = new TexRect("lose.png", -1, 1, 2, 2);

    player = new Player(debugModeEnabled);
    movingGameObjects.push_back(player);

    explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.3, 0.4, false);

    // for DEMO
    demo = new Sprite("spiny.png", 1, 16, .64, 0.33, .15, .15, 0, 0, true, spiny);
    singleton = this;

    gameLoop(0);

    spawnFallingObjectLoop(1);

    // prints fps of the game every second
    frameCounter(2);

    playerAnimation(3);
    // explosionAnimiation is id = 4
    // difficultyTimer is id = 5
}

void Game::spawnFallingObject() {
    int rn = rand() % (100 + difficulty);
    if (debugModeEnabled)
        std::cout << rn << std::endl;
    if (rn < 60) {
        if (rn < 20 && rn < (difficulty * 2)) { // at difficulty 1, 60% fruit spawns. difficulty 13 = 40% fruit
            if (rand() % 2) {
                spawn(bomb);
            } else if ((rand() % 2)) { // at difficulty 1: 75% bomb, 25% spiny. at difficulty 13: 50/50
                spawn(spiny);
            } else {
                if (rn < (difficulty * 2)) {
                    spawn(spiny);

                } else {
                    spawn(bomb);
                }
            }
        } else
            spawn(fruit);

    } else if (rn < 71) {
        spawn(bomb);
        if (difficulty > 7) { // double bombs at diff 7 and on
            spawn(bomb);
        }
        if (difficulty > 15) {
            spawn(bomb);
        }

    } else if (rn < 82) {
        if (difficulty > 11) { // double spines at diff 11 and on
            spawn(doubleSpiny);
        } else {
            spawn(spiny);
        }

    } else if (rn < 91) {
        spawn(energy);

    } else if (rn < 100) {
        if (rn > 100 - difficulty) { // health spawn percent = difficulty, max 9%
            spawn(health);
        } else {
            spawn(fruit);
        }
    } else if (difficulty > 2) {
        if (rand() % 2) { // 50% chance of bomb
            spawn(bomb);
            spawn(bomb);

        } else {
            if (rand() % 2) { // 25% chance of double spiny
                spawn(doubleSpiny);
            }
            if (difficulty > 14) { // if diff is high, 100%
                spawn(doubleSpiny);
            } else {
                spawn(spiny);
            }
        }
    }
}

// Made this function in case I want to change the values of these constant later.
void Game::spawn(ID id) {
    float objectX = (rand() % 190) / 100.0 - 1.0;
    if (debugModeEnabled)
        std::cout << "ID: " << id << std::endl;
    switch (id) {
    case fruit:
        switch (rand() % 4) {
        case 0:
            movingGameObjects.push_back(new Sprite("banana.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
            break;

        case 1:
            movingGameObjects.push_back(new Sprite("mango.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
            break;

        case 2:
            movingGameObjects.push_back(new Sprite("apple.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
            break;

        case 3:
            movingGameObjects.push_back(new Sprite("grape.png", objectX, 1.2, .1, .1, 0, -.01, fruit));
            break;
        }
        break;

    case spiny:
        movingGameObjects.push_back(new Spiny());
        break;

    case doubleSpiny:
        movingGameObjects.push_back(new Spiny(0));
        movingGameObjects.push_back(new Spiny(1));

        break;
    case bomb:
        movingGameObjects.push_back(new Sprite("bomb.png", objectX, 1.2, .15, .15, 0, -.01, bomb));
        break;

    case health:
        movingGameObjects.push_back(new Sprite("health.png", objectX, 1.2, .1, .1, 0, -.01, health));
        break;

    case energy:
        movingGameObjects.push_back(new Sprite("energy.png", objectX, 1.2, .1, .15, 0, -.01, energy));
        break;
    }
}

void Game::idle() {
}

void Game::keyDown(unsigned char key, float x, float y) {
    if (key == ' ' && preGame) {
        preGame = false;
        demo->setX(1.5);
        seconds = 0;
        // delete demo;

    } else if (key == 'a' || key == 'A') {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
        player->setIsFacingLeft(1);

    } else if (key == 'd' || key == 'D') {
        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        player->setIsFacingLeft(0);

    } else if (key == 'w' || key == 'W') {
        player->jump();

    } else if (key == 'p' || key == 'P') {
        paused = !paused;
        glutPostRedisplay();
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

    if (gameOver) {
        lossScreen->draw();
    } else {
        if (preGame) {
            infoScreen->draw();
            demo->draw();
        } else if (paused) {
            pauseScreen->draw();
        } else {
            bg->draw();
        }

        for (auto i = movingGameObjects.begin(); i != movingGameObjects.end(); i++) {
            (*i)->draw();
            if (debugModeEnabled)
                (*i)->showBounds();
        }
        if (showExplosion) {
            explosion->draw();
        }
    }
    if (!preGame)
        hud->draw();
}

Game::~Game() {
    for (auto i = movingGameObjects.begin(); i != movingGameObjects.end(); i++) {
        delete *i;
    }
    delete infoScreen;
    delete hud;
    delete demo;
    delete explosion;
    delete bg;
    delete pauseScreen;
    delete lossScreen;
}