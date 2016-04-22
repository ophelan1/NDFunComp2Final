#ifndef BULLET_H
#define BULLET_H

#include <math.h>
#include "sprite.h"
#include "object.h"
#include <iostream>
#include <list>
#include "boom.h"

class Bullet : public object{
    public:
        static const int ACCEL_Y = 0.22*SCALE;
        Bullet(int x, int y, int angle, int power); 
        void drawSprite(SDL_Surface* screen);
        void onUpdate();
        bool is_dead();
        void onDeath(list<object*>*);
    private:
        int yStart;
        Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Bullet::Bullet(int x, int y, int angle, int power) : sprite("bullet.png")
{
    type = 1;
    dxVal = power*SCALE*cos(angle * M_PI / 180.0);
    dyVal = -power*SCALE*sin(angle * M_PI / 180.0);
    xPos = x*SCALE + dxVal;
    yPos = y*SCALE + dyVal;
    yStart = yPos;
}
//################ BASIC UTILITIES ############################

void Bullet::onDeath(list<object*>* li)
{
    if (yPos > yStart)
        yPos = yStart;
    li->push_back(new Boom(xPos/SCALE, yPos/SCALE));
}

bool Bullet::is_dead()
{
    return yPos > yStart || type == 0;
}

void Bullet::onUpdate()
{
    dyVal += ACCEL_Y;
    xPos += dxVal;
    yPos += dyVal;
}

void Bullet::drawSprite(SDL_Surface* screen)
{
    sprite.draw(screen,xPos/SCALE - sprite.getWidth()/2, yPos/SCALE - sprite.getHeight()/2);
}

#endif
