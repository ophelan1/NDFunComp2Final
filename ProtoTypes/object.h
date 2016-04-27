#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <SDL/SDL.h>

using namespace std;
enum typing{
    NONE,
    TANK,
    BULLET,
    EXPLOSION,
    BLOCK
};
class object{
	public:
		static const int SCALE = 100;
		object();			
        virtual ~object() { }
		int get_x(void);						//ALL FUNCTIONS WHICH RETURN OBJECT VALUES START W/ 'get'
		int get_y(void);
		int get_dx(void);						//ALL FUNCTIONS WHICH RETURN OBJECT VALUES START W/ 'get'
		int get_dy(void);								
		void change_x(int);					//ALL FUNCTIONS WHICH CHANGE OBJECT VALUES START W/ 'change'
		void change_y(int);
		void change_dx(int);
		void change_dy(int);
		void makeChange(void);				//ALL FUNCTIONS CONCERNED WITH ANIMATION (UPDATING POSITIONS) START W/ 'make'				
		virtual void onUpdate(const unsigned char* state, set<int>* taps){ onUpdate(); }
        virtual void onUpdate() = 0;
        virtual bool is_dead() = 0;
        virtual void drawSprite(SDL_Surface* screen) = 0;
        virtual void onDeath(list<object*>* a){ }
        virtual void kill(){type = NONE;}
        virtual void checkCollision(object& a){ }
        int getType(){return type;}
	protected:
		int xPos;
		int yPos;
		int dxVal;
		int dyVal;
        typing type;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

	object::object(){
        type = NONE;
/*
  	cout << "Please Enter a Value for the xPos: " << endl;
  	std::cin >> xPos;
  	cout << "Please Enter a Value for the yPos: " << endl;
  	cin >> yPos;
  	dxVal=1;
  	dyVal=0;
*/
	}
//############# BASIC RETURN FUNCTIONS ########################
	
	int object::get_x(){
		return xPos/SCALE;
	}

	int object::get_y(){
		return yPos/SCALE;
	}

	int object::get_dx(){
		return dxVal;
	}

	int object::get_dy(){
		return dyVal;
	}

//################ BASIC UTILITIES ############################

	void object::change_x(int xChange){
		xPos=xPos+xChange;
	}

	void object::change_y(int yChange){
		yPos=yPos+yChange;
	}

	void object::change_dx(int dxChange){
		dxVal=dxVal+dxChange;
	}

	void object::change_dy(int dyChange){
		dyVal=dyVal+dyChange;
	}
	void object::makeChange(){
		xPos=xPos+dxVal;
		yPos=yPos+dyVal;
	}


#endif










