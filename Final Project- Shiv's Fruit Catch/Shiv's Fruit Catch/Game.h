#pragma once

#include "Player.h"
#include "HUD.h"
#include <vector>

class Game {
    static const float PLAYER_BASE_SPEED;

    HUD* hud;

    std::vector<Sprite *> objects;

    TexRect *bg;
    Player *player;

    Sprite *explosion;

    int lost;
    bool showExplosion;

    //Whether or not to turn on certain debugging features
    bool debugModeEnabled;

  public:
    Game();

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    void specialKeyUp(int key, float x, float y);
    void idle();

    void createFruit();

    friend void gameLoop(int id);
    friend void spawnFruit(int id);
    friend void playerAnimation(int id);
    friend void explosionAnimation(int id);

    ~Game();
};