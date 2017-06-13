#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debugMode 0

int countSentences(char *buffer) {
	
	char delimiter[] = ".";

	return parse(buffer, delimiter, debugMode);
}
