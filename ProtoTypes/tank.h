#ifndef TANK_H
#define TANK_H

#include "sprite.h"
#include "object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_keyboard.h>
#include <iostream>
#include <string>

using namespace std;

class Tank : public object{
	public:
		Tank(int left, int right, int minX, int maxX, int up, int down);
		void drawSprite(SDL_Surface* screen);
		void onUpdate(const unsigned char* state);
	private:
		int dxMax;
		int xMax;
		int xMin;
        	int key_left;
	        int key_right;
		int key_up;
		int key_down;
		static const int SCALE = 100;
		static const int ACCEL_X = 0.25*SCALE;
		static const int FRICTION_X = 0.1*SCALE;
	        Sprite sprite;
		Sprite turret;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

    Tank::Tank(int left, int right, int minX, int maxX, int up, int down) : sprite(), turret("line360.png",0,0,32,32,360) {
        xPos = 300*SCALE;
        yPos = 600*SCALE;
        dxVal = 0;
        dyVal = 0;
        dxMax = 4*SCALE;
        xMax = maxX*SCALE;
        xMin = minX*SCALE;
        key_left = left;
        key_right = right;
	key_up = up;
	key_down = down;
	turret.setFrame(90);
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(const unsigned char* state){
        const int sprite_width = sprite.getWidth()*SCALE;
        if (state[ key_left ] && (dxVal > -dxMax) && (xPos > xMin))
            dxVal -= ACCEL_X;
        else if (state[ key_right ] && (dxVal < dxMax) && (xPos + sprite_width < xMax))
            dxVal += ACCEL_X;
	else if (dxVal != 0)
		dxVal += dxVal > 0? -FRICTION_X:FRICTION_X;

	if ((dxVal>0?dxVal:-dxVal) < FRICTION_X)
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

	if (state[ key_up ])
		turret.incFrame(1);

	if (state[ key_down ])
		turret.incFrame(-1);
    }

    void Tank::drawSprite(SDL_Surface* screen){
        sprite.draw(screen,xPos/SCALE,yPos/SCALE);
	turret.draw(screen,xPos/SCALE,yPos/SCALE);
    }

#endif
