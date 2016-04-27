/*boom.h
 *
 * Defines the explosion effect class, Boom.
 * Just a simple animation that removes itself upon completion.
 */
#ifndef BOOM_H
#define BOOM_H

#include "sprite.h"
#include "object.h"
#include <string>

class Boom : public object{
    public:
        // constructor
        Boom(int x, int y, std::string file="boom.png", int num=7, int w=64, int h=64); 
        // called for drawing
        void drawSprite(SDL_Surface* screen);
        // called every frame
        void onUpdate();
        // called to check if we have ended
        bool is_dead();
        // ignore collisions
        void onCollision(object& a){ }
    private:
        // the sprite we will be drawing
	    Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Boom::Boom(int x, int y, std::string file, int num, int w, int h) : sprite(file, 0, 0, w, h, num)
{
    type = EXPLOSION;
    xPos = x*SCALE;
    yPos = y*SCALE;
}
//################ BASIC UTILITIES ############################
// return whether we are on the last frame
bool Boom::is_dead(){
    return sprite.getFrame() == sprite.getFrames()-1;
}
// increment our image frame
void Boom::onUpdate(){
   sprite.incFrame(1);
}
// draw ourselves
void Boom::drawSprite(SDL_Surface* screen){
    sprite.draw(screen,xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
}

#endif
