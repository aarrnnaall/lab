#include "tp2.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define debug 0

void dadController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2]) {
	
	int writeDescriptors[2], nread = 0;
	char amount[16];

	char * const preString = "Number of chars in file:";
	char *message = malloc(100);
	memset(message,'\0',100);

	writeDescriptors[0] = pipe1fd[WRITE_END];
	writeDescriptors[1] = pipe2fd[WRITE_END];

	close(pipe1fd[READ_END]);
	close(pipe2fd[READ_END]);
	close(pipe3fd[WRITE_END]);

	//Read from stdin or file and write to pipes
	readAndPassItOn(conf,writeDescriptors);
				
	close(pipe1fd[WRITE_END]);
	close(pipe2fd[WRITE_END]);

	while( (nread=read(pipe3fd[READ_END],amount,sizeof(amount))) > 0) {
		if (snprintf(message,strnlen(preString,100)+nread+2,"%s%s\n",preString,amount) < 0) {
			perror("snprintf");
		}
		write(STDOUT_FILENO,message,strnlen(message,100));
	}
	//Wait for second child to finish ???
	
	close(pipe3fd[READ_END]);
}
