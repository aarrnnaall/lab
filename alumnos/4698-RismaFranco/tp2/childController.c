#include "tp2.h"
#include "macros.h"

#include "unistd.h"
#define debug 0

void childController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2], int child) {
	if (child == 0) {
		// First Child
		close(pipe1fd[WRITE_END]);
       	close(pipe2fd[WRITE_END]);
       	close(pipe2fd[READ_END]);
       	close(pipe3fd[READ_END]);
       
		readAndCount(conf, pipe1fd[READ_END], pipe3fd[WRITE_END]);
       
		close(pipe1fd[READ_END]);
		close(pipe3fd[WRITE_END]);
	} else {
		// Subsequent child
  		close(pipe1fd[READ_END]);
		close(pipe1fd[WRITE_END]);
		close(pipe2fd[WRITE_END]);
		close(pipe3fd[READ_END]);
		close(pipe3fd[WRITE_END]);
					
		capitalizeAndSaveToFile(conf,pipe2fd[READ_END]);      
       
		close(pipe2fd[READ_END]);
	}
}
