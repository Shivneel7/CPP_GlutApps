#pragma once

#include "Game.h"
#include <iostream>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Game::Game(int w, int h) : windowW(w), windowH(h){

    ship = new Ship();

    enemy = new Rect(-.125,.75, .25,.25,1,0,0);

    bulletSpeed = .004;

    win = loss = false;
}

void Game::draw(){
    
    if(win){
        renderText("YOU WIN!", -.1, .1);
    }else{
        enemy->draw();
    }

    if(loss){
        renderText("GAME OVER d:^(", -.2, .1);
    }else{
        ship->draw();
        for(Rect* r : bullets){
            r->draw();
        }
    }
}


void Game::keyDown(unsigned char key, float x, float y) {
    if(!loss){
        ship->keyDown(key,x,y);
        if(key == ' '){
            fire();
        }
    }
}

void Game::keyUp(unsigned char key, float x, float y){
    if(!loss)
        ship->keyUp(key,x,y);
}

void Game::idle(){
    
    if(!loss){
        ship->idle();

        if(!win && checkCollision(*ship,*enemy)){
            loss = true;
        }

        for(Rect* r : bullets){
            //move bullet up
            r->setY(r->getY() + bulletSpeed);
            if(!win && checkCollision(*r,*enemy)){
                win = 1;
            }
        }
    }
    
}

void Game::fire(){
    bullets.push_front(new Rect(ship->getX() + ship->getW()/2 - .03, ship->getY(), .05,.1,1,1,1));
}

void Game::renderText(std::string text, float x, float y){
    glColor3f(1, 1, 1);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x+offset, y-2*(float)glutBitmapHeight(GLUT_BITMAP_TIMES_ROMAN_24)/windowH);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        offset += (2*(float)glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, text[i]) / windowW);
    }
}

bool Game::checkCollision(const Rect& one, const Rect& two) const{
    
    return  (one.getX() < (two.getX() + two.getW()) && two.getX() < (one.getX() + one.getW())) &&
            (one.getY() > (two.getY() - two.getH()) && two.getY() > (one.getY() - one.getH()));
}

Game::~Game(){
    for(Rect* r : bullets){
        delete r;
    }
    delete ship;
    delete enemy;
}