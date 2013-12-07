/*
 * Pawel Kubik
 * Warsaw University of Technology
 * EiTI
 * 
 * readkey
 * Simple unbuffered input
 */

#include <unistd.h>
#include "readkey.h"

TermiosStates termstat;

int initReadKey() {
	if (tcgetattr(0, &termstat.original)) {
		return 1;	//error getting current term settings
	}
	termstat.modified = termstat.original;
	termstat.modified.c_lflag &= ~ICANON;
	termstat.modified.c_lflag |= ECHO;
}

int readKey(char* buff) {	//buff - char[3]
	if (tcsetattr(0, TCSANOW, &termstat.modified)){
		return 1;	//error of switching terminal mode
	}
	else if (tcgetattr(0, &termstat.modified)){
		tcsetattr(0, TCSANOW, &termstat.original);
		return 1;	//same as above
	}
	else if ((termstat.modified.c_lflag & ICANON) || !(termstat.modified.c_lflag & ECHO)) {
		tcsetattr(0, TCSANOW, &termstat.original);
		return 2; //error applying all settings
	}
	buff[0] = buff[1] = buff[2] = 0;
	read(0, buff, 3);
	tcsetattr(0, TCSANOW, &termstat.original);
}