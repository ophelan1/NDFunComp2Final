#ifndef TANK_H
#define TANK_H

#include <SDL/SDL.h>
#include <iostream>
#include "object.h"
#include <list>

using namespace std;

enum SCENE{
	MAIN_MENU,
	TWO_PLAYER
};

class Scene{
	public:
		void onDraw(SDL_Surface* screen) = 0;
		SCENE onUpdate(const unsigned char* state) = 0;
};
