#include "tp2.h"
#include "macros.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define debug 0

void readAndCount(configuration *conf, int readEnd, int writeEnd) {

	int nread=0;	
	char buff[1024];
	char result[8];
	int tokens = 0;

	while ( (nread=read(readEnd,buff,sizeof(buff))) > 0 ) {
			tokens += countWords(buff);	
	}
	if (debug) printf("%s\tTokens count: %d\n",__FILE__,tokens);

	//Convertir el int a string
	snprintf(result,sizeof tokens,"%d",tokens);
	//result[strlen(result)] = '\0';
	
	if (debug) printf("%s\tcantidad de palabras en string: %s\n",__FILE__,result);
	if ( write(writeEnd,result,strlen(result)) < 0 ) {
		perror("write");
	}

	return;
}
