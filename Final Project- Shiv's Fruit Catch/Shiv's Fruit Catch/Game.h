#pragma once

#include "Player.h"
#include "HUD.h"
#include <vector>

class Game {
    static const float PLAYER_BASE_SPEED;

    HUD* hud;

    std::vector<Sprite *> movingGameObjects;
    
    TexRect *bg;
    TexRect *pauseScreen;
    TexRect *lossScreen;
    

    Player *player;

    Sprite *explosion;

    bool gameOver;
    bool showExplosion;
    bool paused;

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

    void createFallingObject();

    friend void gameLoop(int id);
    friend void spawnFallingObjectLoop(int id);
    friend void playerAnimation(int id);
    friend void explosionAnimation(int id);

    ~Game();
};