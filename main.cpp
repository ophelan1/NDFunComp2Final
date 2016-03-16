#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <regex>
#include "object.h"

using namespace std;

int main(void){
	object thing;

	while(1){
		cout << string( 100, '\n' );
		cout << "X-Position = " << thing.get_x() << endl;
		cout << "Y-Position = " << thing.get_y() << endl;
		cout << "Delta X    = " << thing.get_dx() << endl;
		cout << "Delta Y    = " << thing.get_dy() << endl;
		sleep(1);
		thing.makeChange();
	}
}