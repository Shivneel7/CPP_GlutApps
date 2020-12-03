#pragma once

#include "Fruit.h"
#include "MovingSprite.h"
#include "Player.h"
#include "Sprite.h"
#include "TexRect.h"
#include "Text.h"
#include <vector>

class Game {
    static const float PLAYER_BASE_SPEED;

    std::vector<Rect*> hud;
    std::vector<MovingSprite *> objects;

    Player *player;

    Text* s;
    int score;
    
  public:
    Game();

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    void specialKeyUp(int key, float x, float y);
    void idle();

    friend void gameLoop(int id);
    friend void spawnBanana(int id);

    ~Game();
};