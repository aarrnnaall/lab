#include "macros.h"

#ifndef TP2_H_
    #define TP2_H_

  	// Structure for the arguments parsing. Will be filled by optionsHandler()
	typedef struct {
		int inputFileFlag;
		char inputFile[FILENAME_LENGHT];
		char outputFile[FILENAME_LENGHT];
	} configuration;
	
	// Statup arguments handling
    void optionsHandler (int argc, char* const argv[], configuration *conf);

    // Pipe wrapper
    void Pipe(int pipefd[2]);
    
	// Fork and process input
	void flowController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2]);
	
	// Dad handler
	void dadController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2]);

	// Child handler
	void childController(configuration *conf, int pipe1fd[2], int pipe2fd[2], int pipe3fd[2], int child);
	
	// Read input and write into pipes
    void readAndPassItOn(configuration *conf, int writeDesc[2]);

	// Read input and parse words
    void readAndCount(configuration *conf, int readEnd, int writeEnd);

    // CountWords
    int countWords(char *buffer);

	// Capitalize	
	void capitalizeAndSaveToFile(configuration *conf, int readEnd);

    // Dad: show results
    void showResults(int pipe3r, configuration *conf);

#endif
