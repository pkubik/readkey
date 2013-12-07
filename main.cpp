#include "readkey.h"
#include <iostream>
#include <cstdlib>

int main() {
	initReadKey();
	char c[3] = {0, 0, 0};
	while(c[0] != 27 || c[1] != 0) { //while not ESC
		readKey(c);
		system("clear");
		std::cout<<c[0]<<" "<<c[1]<<" "<<c[2]<<"\n";
		std::cout<<static_cast<int>(c[0])<<" "<<static_cast<int>(c[1])<<" "<<static_cast<int>(c[2])<<"\n";
	}
}

