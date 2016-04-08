#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <regex>
#include <SDL/SDL.h>
#include "sprite.h"

using namespace std;

int main(void){

	int xPos, yPos, dx, dy;						//user defined	
	int width = 5, height = 10, frames = 100;	//programmer defined
	string filename;

	cout << "Please enter a value for the initial x position: " << endl;
  	cin >> xPos;
  	cout << "Please enter a value for the initial y position: " << endl;
  	cin >> yPos;
  	cout << "Please enter a value for the desired change in x: " << endl;
  	cin >> dx;
  	cout << "PLease enter a value for the desired change in y: " << endl;
  	cin >> dy;

	while(1){
		sprite object("image.png", xPos, yPos, width, height, frames);
		xPos += dx;
		yPos += dy;
		sleep(1);
	}
}