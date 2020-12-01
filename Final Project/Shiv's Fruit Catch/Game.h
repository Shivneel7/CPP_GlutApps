#pragma once

#include "Sprite.h"
#include "TexRect.h"
#include "Text.h"
#include <vector>

class Game {
    std::vector<Shape *> shapes;
    TexRect *player;
    Sprite *explosion;

  public:
    Game();

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void specialKeyDown(int key, float x, float y);

    friend void explosionTimer(int id);

    ~Game();
};