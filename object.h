#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class object{
	public:
		int getx(void);
		int gety(void);
		void changex(int);
		void changey(int);
		void changedx(int);
		void changedy(int);
		void makeChange(void);
		object();

	private:
		int xpos;
		int ypos;
		int dxpos;
		int dypos;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

	object(){

  	cout << "Please Enter a Value for the xPos: " << endl;
  	cin >> xpos;
  	cout << "Please Enter a Value for the yPos: " << endl;
  	cin >> ypos;
	}

//################ BASIC UTILITIES ############################

	int getx(){
		return xpos;
	}

	int gety(){
		return ypos;
	}

	void changex(int xchange){
		xpos=xpos+xchange;
	}

	void changey(int ychange){
		ypos=ypos+ychange;
	}

	void changedx(int dxchange){
		dxpos=dxpos+dxchange;
	}

	void changedy(int dychange){
		dypos=dypos+dychange;
	}
	void makeChange(){
		xpos=xpos+dxpos;
		ypos=ypos+dypos;
	}











