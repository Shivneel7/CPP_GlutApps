#pragma once

#include "Sprite.h"
#include "TexRect.h"
#include "Text.h"
#include "Player.h"
#include "MovingTexRect.h"
#include <vector>

class Game {
    std::vector<Shape *> shapes;
    std::vector<MovingTexRect *> movingShapes;

    Player *player;
    Sprite *explosion;

  public:
    Game();

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    void keyUp(unsigned char key, float x, float y);
    void specialKeyUp(int key, float x, float y);
    void idle();
    
    friend void explosionTimer(int id);
    friend void timer(int id);

    ~Game();
};