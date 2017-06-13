#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debugMode 0

int countWords (char *buffer) {

	char delimiter[] = " \n\t\r";

	return parse(buffer,delimiter,debugMode);
}
