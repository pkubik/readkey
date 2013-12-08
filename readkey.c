/*
 * Pawel Kubik
 * Warsaw University of Technology
 * EiTI
 * 
 * readkey
 * Simple unbuffered input
 */

#include <unistd.h>
#include <string.h>
#include "readkey.h"

TermiosStates termstat;

int initReadKey() {
	if (tcgetattr(0, &termstat.original)) {
		return -1;	//error getting current term settings
	}
	termstat.modified = termstat.original;
	termstat.modified.c_lflag &= ~ICANON;
	termstat.modified.c_lflag &= ~ECHO;
	return 0;
}

int readKey(char* buff, unsigned int size) {	//buff - char[3]
	if (tcsetattr(0, TCSANOW, &termstat.modified)){
		return -1;	//error of switching terminal mode
	}
	else if (tcgetattr(0, &termstat.modified)){
		tcsetattr(0, TCSANOW, &termstat.original);
		return -1;	//same as above
	}
	else if ((termstat.modified.c_lflag & ICANON) || (termstat.modified.c_lflag & ECHO)) {
		tcsetattr(0, TCSANOW, &termstat.original);
		return -2; //error applying all settings
	}
	memset(buff, 0, size);
	int ret = read(0, buff, size);
	tcsetattr(0, TCSANOW, &termstat.original);
	return ret;
}

int awaitKey() {
	if (tcsetattr(0, TCSANOW, &termstat.modified)){
		return -1;	//error of switching terminal mode
	}
	else if (tcgetattr(0, &termstat.modified)){
		tcsetattr(0, TCSANOW, &termstat.original);
		return -1;	//same as above
	}
	else if ((termstat.modified.c_lflag & ICANON) || (termstat.modified.c_lflag & ECHO)) {
		tcsetattr(0, TCSANOW, &termstat.original);
		return -2; //error applying all settings
	}
	char ch[20];				//the longest keycode is 5
	int ret = read(0, &ch, 20);	//4 such keys at the same needed to exceed 20
	//even though it would cause only small interuption of next readKey (expected when bashing the keyboard)
	tcsetattr(0, TCSANOW, &termstat.original);
	return ret;
}
