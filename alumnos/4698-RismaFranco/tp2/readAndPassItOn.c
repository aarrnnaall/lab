#include "tp2.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#define debug 0

void readAndPassItOn (configuration *conf, int writeDescriptors[2]) {

	int nread = 0, descriptor = -1;
	char buffer[READING_AMOUNT];

	if (conf->inputFileFlag) {
		if ( (descriptor=open(conf->inputFile,O_RDONLY)) == -1){
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (debug) printf("%s\tReading from filename: %s and fd: %d\n",__FILE__,conf->inputFile,descriptor);
	} else {
		if (debug) printf("%s\tReading from STDIN\n",__FILE__);
		descriptor = STDIN_FILENO;
	}

	while ( (nread=read(descriptor,buffer,READING_AMOUNT)) > 0) {
		if (write(writeDescriptors[0],buffer,nread) == -1) {
			perror("write into first fd");
		}
		if (debug) printf("%s\tWriting into fd %d amount %d\n",__FILE__,writeDescriptors[0],nread);
		if (write(writeDescriptors[1],buffer,nread) == -1) {
			perror("write into second fd");
		}
		if (debug) printf("%s\tWriting into fd %d amount %d\n",__FILE__,writeDescriptors[1],nread);
	}
	return;
}
