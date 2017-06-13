#include "tp2.h"
#include "macros.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#define debug 0

void capitalizeAndSaveToFile(configuration *conf, int readEnd) {

	int nread, outputFd;
	char buf[READING_AMOUNT];

	// Open
	if ( (outputFd=open(conf->outputFile,O_CREAT|O_APPEND|O_WRONLY,S_IRWXU|S_IRWXG)) < 0) {
		perror("open");
		_exit(-1);
	}
	if (debug) printf("%s\tSuccessfully opened: %s descriptor %d\n",__FILE__,conf->outputFile,outputFd);
	
	if (debug) printf("%s\tStart reading process from desc: %d\n",__FILE__,readEnd);
	while( (nread=read(readEnd,buf,READING_AMOUNT)) > 0 ) {
		if (nread == -1) {
			perror("read");
			_exit(-1);
		}
		if (debug) printf("%s\treading %s chars lenght %d\n",__FILE__,buf,nread);
	
		int i;
		for (i=0;i<strlen(buf);i++) {
			buf[i] = toupper(buf[i]);
			i++;
		}

		write(outputFd,buf,nread);
		if (debug) printf("%s\twrite to fd %d string: %s length: %d\n",__FILE__,outputFd,buf,nread);
		memset(buf,'\0',READING_AMOUNT);
	}

	if (debug) printf("%s\tEnd reading process from desc: %d\n",__FILE__,readEnd);
	close(outputFd);

	return;
}
