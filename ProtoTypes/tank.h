#ifndef TANK_H
#define TANK_H

#include "sprite.h"
#include "object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_keyboard.h>
#include <iostream>

using namespace std;

class Tank : public object{
	public:
		Tank();
		void drawSprite(SDL_Surface* screen);
		void onUpdate(const unsigned char* state);
	private:
		int dxMax;
		int xMax;
		int xMin;
		Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

    Tank::Tank() : sprite() {
	xPos = 300;
	yPos = 300;
        dxVal = 0;
        dyVal = 0;
	dxMax = 8;
	xMax = 600;
	xMin = 0;
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(const unsigned char* state){
        if (state[ SDLK_LEFT ] && (dxVal > -dxMax) && (xPos > xMin))
            dxVal--;
        else if (state[ SDLK_RIGHT ] && (dxVal < dxMax) && (xPos < xMax))
            dxVal++;
	else if (dxVal != 0)
		dxVal += dxVal > 0? -1:1;


	xPos += dxVal;	

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
        sprite.draw(screen,xPos,yPos);
    }

#endif
