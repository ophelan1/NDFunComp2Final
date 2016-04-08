#ifndef TANK_H
#define TANK_H

#include "sprite.h"
#include "object.h"
#include <SDL/SDL.h>


using namespace std;

class Tank : public object{
	public:
		tank();
        void drawSprite(SDL_Surface* screen);
        void onUpdate(unsigned char state*);
	private:
        int dxMax = 4;
        int xMax = 600;
        int xMin = 0;
        Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

    Tank::Tank() : sprite() {
        dxVal = 0;
        dyVal = 0;
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(unsigned char state*){
        if (state[ SDL_SCANCODE_LEFT ] && dxVal > -dxMax && xPos > xMin)
            dxVal--;
        else if (state[ SDL_SCANCODE_RIGHT ] && dxVal < dxMax && xPos < xMax)
            dxVal++;
        else
            dxVal = 0;

        if (xPos < xMin){
            dxVal = 0;
            xPos = xMin;
        }
        if (xPos > xMax){
            dxVal = 0;
            xPos = xMax;
        }
    }

    void Tank::drawSprite(SDL_Surface* screen){
        sprite.draw(screen,x,y);
    }

#endif
