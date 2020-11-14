#ifndef Game_h
#define Game_h

#include "Ship.h"
#include "Rect.h"
#include <string>
#include <deque>

class Game{

    Ship* ship;
    Rect* enemy;
    std::deque<Rect*> bullets;
    
    float bulletSpeed;
    bool win, loss;
    int windowW, windowH;

    public:
        Game(int , int );

        void draw();

        void keyDown(unsigned char key, float x, float y);

        void keyUp(unsigned char key, float x, float y);

        void idle();

        void fire();

        void renderText(std::string text, float x, float y);

        bool checkCollision(const Rect& one, const Rect& two) const;

        ~Game();
};


#endif