#include "tp2.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define debug 0

int countWords(char *buffer) {
	
	int count = 0;
	char *token, *ptr;

	char delimiter[] = " \n\t\r";
	
	token = strtok_r(buffer,delimiter,&ptr);
	if (!token) {
		return 0;
	}
	count++;
	if (debug) printf("%s\tToken[%d]: %s\n",__FILE__,count,token);

	while ( (token=strtok_r(NULL,delimiter,&ptr)) != NULL ) {
		count++;
		if (debug) printf("%s\tToken[%d]: %s\n",__FILE__,count,token);
	}

	if (debug) printf("%s\tTokens totales en la pasada: %d\n",__FILE__,count);
	return count;
}
