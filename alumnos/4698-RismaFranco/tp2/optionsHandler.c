
#include <assert.h>

#include "tp2.h"
#include "macros.h"

#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define debug 0

void optionsHandler (int argc, char* const argv[], configuration *conf){

    int opt = 0;

	// Configure default values
	strncpy(conf->outputFile,DEFAULT_FILENAME,strnlen(DEFAULT_FILENAME,FILENAME_LENGHT)+1);
	conf->inputFileFlag = 0;

    // Argument handling
    opterr=1;   // Disables getopt() error printing.
	while ((opt = getopt(argc, argv, "o:i:h")) >= 0 ){   //i:input Filename  o:output Filename   h:help
		switch (opt){
            case 'i':
				strncpy(conf->inputFile,optarg,strnlen(optarg,FILENAME_LENGHT)+1);
                conf->inputFileFlag=1;
                if (debug) printf("File to read from: %s\n",conf->inputFile);
                break;
            case 'o':
				strncpy(conf->outputFile,optarg,strnlen(optarg,FILENAME_LENGHT)+1);
                if (debug) printf("File to save results: %s\n",conf->outputFile);
                break;
            case 'h':
                printf("Uso: %s -[args]\nArgumentos:\ni\tInput filename.\no\tOutput file name.\nh\tHelp\n",argv[0]);
                exit(EXIT_SUCCESS);
			case '?':
                printf("Uso: %s -[args]\nArgumentos:\ni\tInput filename.\no\tOutput file name.\nh\tHelp\n",argv[0]);
                exit(EXIT_SUCCESS);
            default:
                printf("Ambiguous sintax. Run: %s -h to get help\n",argv[0]);
                exit(EXIT_SUCCESS);
		}
	}
}
