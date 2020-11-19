#ifndef Ship_h
#define Ship_h

#include "Rect.h"

class Ship: public Rect{
    float dx, dy, speed;

    public:
        Ship();

        void idle();

        void keyUp(unsigned char key, float x, float y);
        void keyDown(unsigned char key, float x, float y);
        float getSpeed() const;
};



#endif