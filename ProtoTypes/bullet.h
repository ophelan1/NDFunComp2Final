/*bullets.h
 *
 * The bullet class.
 */
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
        // the downward acceleration constant
        static const int ACCEL_Y = 0.22*SCALE;
        // constructor
        Bullet(int x, int y, int angle, int power); 
        // called on draw event
        void drawSprite(SDL_Surface* screen);
        // called on frame update
        void onUpdate();
        // called to check our living status (did we hit something)
        bool is_dead();
        // our death action (add a boom)
        void onDeath(list<object*>*);
    private:
        int yStart;
        Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
// cpmstructor
Bullet::Bullet(int x, int y, int angle, int power) : sprite("bullet.png")
{
    type = BULLET;
    // convert from polar (angle, power) to rectangular (x,y)
    dxVal = power*SCALE*cos(angle * M_PI / 180.0);
    dyVal = -power*SCALE*sin(angle * M_PI / 180.0);
    // move one frame, so we don't hit the tank that shot us
    xPos = x*SCALE + dxVal;
    yPos = y*SCALE + dyVal;
    // ystart used to tell if we hit the ground
    yStart = yPos;
}
//################ BASIC UTILITIES ############################

void Bullet::onDeath(list<object*>* li)
{
    // don't go beneath the floor
    if (yPos > yStart)
        yPos = yStart; // lost and insecure, you found me, you found me, lying on the floor
    // add a boom 
    li->push_back(new Boom(xPos/SCALE, yPos/SCALE));
}
// If we hit the ground or anything else
bool Bullet::is_dead()
{
    return yPos > yStart || type == NONE;
}
// move
void Bullet::onUpdate()
{
    dyVal += ACCEL_Y;
    xPos += dxVal;
    yPos += dyVal;
}
// draw ourselves
void Bullet::drawSprite(SDL_Surface* screen)
{
    sprite.draw(screen,xPos/SCALE - sprite.getWidth()/2, yPos/SCALE - sprite.getHeight()/2);
}

#endif
