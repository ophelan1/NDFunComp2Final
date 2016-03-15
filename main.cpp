#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <regex>
#include "object.h"

int main(void){
	object thing;
	cout << "X-Position = " << thing.getx() << endl;
	cout << "Y-Position = " <<thing.gety() << endl;
}