#ifndef BOOM_H
#define BOOM_H

#include "sprite.h"
#include "object.h"

class Boom : public object{
    public:
        Boom(int x, int y); 
        void drawSprite(SDL_Surface* screen);
        void onUpdate();
        bool is_dead();
        void onCollision(object& a){ }
    private:
	    Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Boom::Boom(int x, int y) : sprite("boom.png", 0, 0, 64, 64, 7)
{
    xPos = x*SCALE;
    yPos = y*SCALE;
}
//################ BASIC UTILITIES ############################

bool Boom::is_dead(){
    return sprite.getFrame() == 6;
}

void Boom::onUpdate(){
   sprite.incFrame(1);
}

void Boom::drawSprite(SDL_Surface* screen){
    sprite.draw(screen,xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
}

#endif
