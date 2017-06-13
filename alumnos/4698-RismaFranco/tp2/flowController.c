#include "tp2.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debug 0

void flowController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2]){
    
  	int i = 0;
    pid_t childpid=0;

    for (i=0; i<DEFAULT_CHILDS; i++){
    	switch ((childpid=fork())){
      		case -1: // Error
        		perror("fork");
        		_exit(EXIT_FAILURE);
      		case 0: // Son
				childController(conf, pipe1fd, pipe2fd, pipe3fd, i);	
				_exit(EXIT_SUCCESS); // Kill the son
		}
	}

	dadController(conf, pipe1fd, pipe2fd, pipe3fd);	
	if (debug) puts("El padre muriendo");
	_exit(EXIT_SUCCESS);
}
