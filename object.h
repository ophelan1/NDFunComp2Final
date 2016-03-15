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
		object();			
		int get_x(void);						//ALL FUNCTIONS WHICH RETURN OBJECT VALUES START W/ 'get'
		int get_y(void);								
		void change_x(int);					//ALL FUNCTIONS WHICH CHANGE OBJECT VALUES START W/ 'change'
		void change_y(int);
		void change_dx(int);
		void change_dy(int);
		void makeChange(void);				//ALL FUNCTIONS CONCERNED WITH ANIMATION (UPDATING POSITIONS) START W/ 'make'				

	private:
		int xPos;
		int yPos;
		int dxVal;
		int dyVal;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

	object::object(){

  	cout << "Please Enter a Value for the xPos: " << endl;
  	std::cin >> xPos;
  	cout << "Please Enter a Value for the yPos: " << endl;
  	cin >> yPos;
	}

//################ BASIC UTILITIES ############################

	int object::get_x(){
		return xPos;
	}

	int object::get_y(){
		return yPos;
	}

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










