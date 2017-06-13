#include "tp1.h"
#include "stdio.h"
#include "string.h"

#define debugMode 0

int countSpecialChars(char *buffer) {

	int i=0, sum=0;

	for (i=0; i<strnlen(buffer,1024); i++) {
		if ( !((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z') || (*buffer >= '0' && *buffer <= '9') || (*buffer==' ') || (*buffer =='\n')) ) {
			sum++;
			if (debugMode) printf("\nSpecial Found: %c",*buffer);
		}
		buffer++;
	}
	if (debugMode) printf("\nSpecial sum: %d",sum);
	return sum;
}
