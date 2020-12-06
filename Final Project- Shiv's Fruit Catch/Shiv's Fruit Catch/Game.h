#pragma once

#include "HUD.h"
#include "Player.h"
#include "Spiny.h"
#include <vector>

class Game {
    static const float PLAYER_BASE_SPEED;

    //how often in seconds to ramp up the Difficulty
    static const int DIFFICULTY_INCREASE_MODIFIER = 10;

    HUD *hud;

    std::vector<Sprite *> movingGameObjects;

    TexRect *infoScreen;
    Sprite *demo;
    TexRect *bg;
    TexRect *pauseScreen;
    TexRect *lossScreen;

    Player *player;

    Sprite *explosion;

    bool preGame;
    bool gameOver;
    bool showExplosion;
    bool paused;

    //increases as game goes on. Controls bomb, fruit, and health upgrade spawn rate
    int difficulty;
    // Whether or not to turn on certain debugging features
    bool debugModeEnabled;

  public:
    Game();

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    void specialKeyUp(int key, float x, float y);
    void idle();

    //controls spawnRates of the specific objects
    void spawnFallingObject();
    void spawn(ID id);

    friend void gameLoop(int id);
    friend void spawnFallingObjectLoop(int id);
    friend void playerAnimation(int id);
    friend void explosionAnimation(int id);
    friend void difficultyTimer(int id);

    ~Game();
};