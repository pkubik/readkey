/*
 * Pawel Kubik
 * Warsaw University of Technology
 * EiTI
 * readkey.h
 * Simple unbuffered input
 */

#include <termios.h>

#ifndef READKEY_H
#define	READKEY_H

typedef struct {
	struct termios modified;
	struct termios original;
} TermiosStates;

int initReadKey();
//1 - error getting current terminal settings

int readKey(char* buff);
//buff - char[3]
//1 - error switching terminal mode
//2 - error applying all settings

#endif	/* READKEY_H */
