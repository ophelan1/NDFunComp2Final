#ifndef BULLET_H
#define BULLET_H

#include <math.h>
#include "sprite.h"
#include "object.h"
#include <iostream>

class Bullet : public object{
    public:
        static const int ACCEL_Y = 0.25*SCALE;
        Bullet(int x, int y, int angle, int power); 
        void drawSprite(SDL_Surface* screen);
        void onUpdate();
    private:
        Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Bullet::Bullet(int x, int y, int angle, int power) : sprite("bullet.png")
{
    xPos = (x-sprite.getWidth()/2)*SCALE;
    yPos = (y-sprite.getHeight()/2)*SCALE;
    dxVal = power*SCALE*cos(angle * M_PI / 180.0);
    dyVal = -power*SCALE*sin(angle * M_PI / 180.0);
}
//################ BASIC UTILITIES ############################


void Bullet::onUpdate(){
    dyVal += ACCEL_Y;
    xPos += dxVal;
    yPos += dyVal;
}

void Bullet::drawSprite(SDL_Surface* screen){
    sprite.draw(screen,xPos/SCALE,yPos/SCALE);
}

#endif
