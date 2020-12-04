#pragma once

#include "MovingTexRect.h"
#include "Player.h"
#include "Sprite.h"
#include "TexRect.h"
#include "Text.h"
#include <vector>

class Game {
    static const float PLAYER_BASE_SPEED;

    std::vector<Rect*> hud;
    std::vector<MovingTexRect *> objects;

    TexRect* bg;
    Player *player;

    Text* s;
    int score, lost;
    
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

    ~Game();
};