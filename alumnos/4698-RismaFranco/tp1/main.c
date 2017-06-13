#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, const char* argv[]) {

	char buff[1024];
	char *aux = (char *) malloc(sizeof(buff));
	int nbytes, words = 0, sentences = 0, special = 0;

	while ( (nbytes=read(STDIN_FILENO,buff,sizeof(buff)) > 0) ) {
		if (nbytes == -1) {
			perror("read");
		}
	
		memset(aux,'\0',1024);
		strncpy(aux,buff,strnlen(buff,1024));
		sentences += countSentences(aux);
		
		memset(aux,'\0',1024);
		strncpy(aux,buff,strnlen(buff,1024));
		words += countWords(aux);
		
		memset(aux,'\0',1024);
		strncpy(aux,buff,strnlen(buff,1024));
		special += countSpecialChars(aux);

		memset(buff,'\0',1024);
	}

	printf("\nSenteces: %d\tWords: %d\tSpecialChars: %d\n", sentences, words, special);

	return 0;
}
