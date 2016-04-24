#ifndef BOOM_H
#define BOOM_H

#include "sprite.h"
#include "object.h"
#include <string>

class Boom : public object{
    public:
        Boom(int x, int y, std::string file="boom.png", int num=7, int w=64, int h=64); 
        void drawSprite(SDL_Surface* screen);
        void onUpdate();
        bool is_dead();
        void onCollision(object& a){ }
    private:
	    Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Boom::Boom(int x, int y, std::string file, int num, int w, int h) : sprite(file, 0, 0, w, h, num)
{
    type = 3;
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
