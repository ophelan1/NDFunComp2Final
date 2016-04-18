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
        static const int ACCEL_Y = 0.12*SCALE;
        Bullet(int x, int y, int angle, int power); 
        void drawSprite(SDL_Surface* screen);
        void onUpdate();
        bool is_dead();
        void kill();
        void onDeath(list<object*>*);
        static int getType(){return 1;}
    private:
        int yStart;
        Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Bullet::Bullet(int x, int y, int angle, int power) : sprite("bullet.png")
{
    type = 0;
    xPos = x*SCALE;
    yPos = y*SCALE;
    yStart = yPos;
    dxVal = power*SCALE*cos(angle * M_PI / 180.0);
    dyVal = -power*SCALE*sin(angle * M_PI / 180.0);
}
//################ BASIC UTILITIES ############################

void Bullet::onDeath(list<object*>* li)
{
    li->push_back(new Boom(xPos/SCALE, yPos/SCALE));
}

void Bullet::kill()
{
    yPos = yStart+1;
}

bool Bullet::is_dead()
{
    return yPos > yStart;
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
