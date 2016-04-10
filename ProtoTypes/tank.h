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
		static const int scale = 100;
		static const int sprite_width = 32*scale;
		static const int accel_x = 0.25*scale;
		static const int friction_x = 0.1*scale;
		Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

    Tank::Tank() : sprite() {
	xPos = 300*scale;
	yPos = 300*scale;
        dxVal = 0;
        dyVal = 0;
	dxMax = 4*scale;
	xMax = 640*scale;
	xMin = 0;
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(const unsigned char* state){
        if (state[ SDLK_LEFT ] && (dxVal > -dxMax) && (xPos > xMin))
            dxVal -= accel_x;
        else if (state[ SDLK_RIGHT ] && (dxVal < dxMax) && (xPos + sprite_width < xMax))
            dxVal += accel_x;
	else if (dxVal != 0)
		dxVal += dxVal > 0? -friction_x:friction_x;

	if ((dxVal>0?dxVal:-dxVal) < friction_x)
		dxVal = 0;

	xPos += dxVal;	

        if (xPos < xMin){
            dxVal = 0;
            xPos = xMin;
        }
        if (xPos + sprite_width> xMax){
            dxVal = 0;
            xPos = xMax- sprite_width;
        }
    }

    void Tank::drawSprite(SDL_Surface* screen){
        sprite.draw(screen,xPos/scale,yPos/scale);
    }

#endif
