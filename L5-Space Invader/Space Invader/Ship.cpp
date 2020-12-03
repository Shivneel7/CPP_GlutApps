#pragma once

#include "Ship.h"
#include <iostream>

Ship::Ship() : Rect::Rect(-.125,-.6, .25,.25,0,0,1), dx(0), dy(0), speed(.002){

}

void Ship::idle(){
    x += dx;
    y += dy;

    //stops ship from leaving screen
    if(x < -1){
        x = -1;
    }
    if(x + w > 1){
        x = 1- w;
    }
    if(y > 1){
        y = 1;
    }
    if(y - h < -1){
        y = -1 + h;
    }
}

void Ship::keyDown(unsigned char key, float x, float y) {
    if(key == 'w'){
        dy += speed;
        std::cout<< dx << std::endl;

    }else if(key == 'a'){
        dx += -speed;

    }else if(key == 'd'){
        dx += speed;

    }else if(key == 's'){
        dy += -speed;
    }
}

void Ship::keyUp(unsigned char key, float x, float y) {
    if(key == 'w'){
        dy += -speed;
    }

    if(key == 's'){
        dy += speed;
    }

    if(key == 'a'){
        dx += speed;
    }

    if(key == 'd'){
        dx += -speed;
    }
}

float Ship::getSpeed() const{
    return speed;
}
