#include "tp1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parse(char *buffer, char *delimiter, int debugMode) {
	
	int count = 0;
	char *token, *ptr;

	token = strtok_r(buffer,delimiter,&ptr);
	if (!token) {
		return 0;
	}
	count++;
	if (debugMode) printf("\nToken[%d]: %s",count,token);

	while ( (token=strtok_r(NULL,delimiter,&ptr)) != NULL ) {
		count++;
		if (debugMode) printf("\nToken[%d]: %s",count,token);
	}

	if (debugMode) printf("\nTokens totales en la pasada: %d",count);
	return count;
}
