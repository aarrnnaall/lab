#include "tp2.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define debug 0

int main(int argc, char **argv) {

	if (debug) printf("------------ Starting %s --------------\n",argv[0]);

  	configuration *conf = (configuration *)malloc(sizeof(configuration));
  	
	int pipe1fd[2], pipe2fd[2], pipe3fd[2];

  	optionsHandler(argc,argv,conf);
	if (debug) printf("Opciones: inputFile: %s\t outputFile: %s\n",conf->inputFile, conf->outputFile);

    Pipe(pipe1fd);
	if (debug) puts("Pipe 1 creted");

    Pipe(pipe2fd);
	if (debug) puts("Pipe 2 created");
	
    Pipe(pipe3fd);
	if (debug) puts("Pipe 3 created");

    // Fork
    flowController(conf, pipe1fd, pipe2fd, pipe3fd);

	return 0;
}

