#include "tp2.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debug 0

void Pipe (int pipefd[2]){
    
    if (pipe(pipefd) == -1){
        perror("error creating pipe");
        exit(EXIT_FAILURE);
    }

	if (debug) printf("%s\tPipe created. Read->%d Write->%d\n",__FILE__,pipefd[0],pipefd[1]);
}
