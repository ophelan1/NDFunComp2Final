#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class object{
	public:
		int getx(void);						//ALL FUNCTIONS WHICH RETURN OBJECT VALUES START W/ 'get'
		int gety(void);								
		void changex(int);					//ALL FUNCTIONS WHICH CHANGE OBJECT VALUES START W/ 'change'
		void changey(int);
		void changedx(int);
		void changedy(int);
		void makeChange(void);				//ALL FUNCTIONS CONCERNED WITH ANIMATION (UPDATING POSITIONS) START W/ 'make'
		object();							

	private:
		int xpos;
		int ypos;
		int dxpos;
		int dypos;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

	object::object(){

  	cout << "Please Enter a Value for the xPos: " << endl;
  	std::cin >> xpos;
  	cout << "Please Enter a Value for the yPos: " << endl;
  	cin >> ypos;
	}

//################ BASIC UTILITIES ############################

	int object::getx(){
		return xpos;
	}

	int object::gety(){
		return ypos;
	}

	void object::changex(int xchange){
		xpos=xpos+xchange;
	}

	void object::changey(int ychange){
		ypos=ypos+ychange;
	}

	void object::changedx(int dxchange){
		dxpos=dxpos+dxchange;
	}

	void object::changedy(int dychange){
		dypos=dypos+dychange;
	}
	void object::makeChange(){
		xpos=xpos+dxpos;
		ypos=ypos+dypos;
	}


#endif










