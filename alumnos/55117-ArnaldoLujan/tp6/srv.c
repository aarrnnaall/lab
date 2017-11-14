#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "service.h"
#include <string.h>
int main(int argc, char **argv)
{
	char buffer[1024],*parciar;
        char *puerto;
        char *dirrecion;
	struct sockaddr_in addr = {};
	int sockfd, conn;
        //|int leido;
	int fd;
          
        if ((fd = open("config.txt",O_RDONLY,S_IREAD)) < 0) {//abrimos archivo de configuracion
                perror("Error de abrir archivo"); 	  
        	                                            }
        read(fd,buffer,sizeof buffer);//leemos el archivo                                                 
 	parciar = strtok(buffer," ");
        dirrecion = strtok(NULL," dirrecion=");
        printf("DIRRECION= %s\n",dirrecion);

        strtok(parciar,"=");
        puerto = strtok(NULL,"=");
        printf("PUERTO= %s\n",puerto);        
         
         
        
       int n = atoi (puerto);  
        sockfd = socket(PF_INET, SOCK_STREAM, 0);
        
	if (sockfd == -1) { 
		perror("socket()");
		exit(EXIT_FAILURE); 
	}

	
        /* ADDR. FAMILY */
	addr.sin_family= AF_INET;
	/* PORT */
       addr.sin_port = htons(n);	
       
	/* ADDRESS */
	inet_pton(AF_INET, dirrecion, &addr.sin_addr);        
	
	if (bind(sockfd, (struct sockaddr *) &addr, sizeof (addr)) < 0) { 
		perror("bind()");
		exit(EXIT_FAILURE); 
	}

	if (listen(sockfd, 5) < 0) { 
		perror("listen()");
		exit(EXIT_FAILURE); 
	}

	while ((conn = accept(sockfd, NULL, 0)) > 0) {
		switch (fork()) {
			case 0:
                close(sockfd);
                service(conn);
				return 0;

			case -1: // error
				perror("fork()");
				return 1;
		}

		close(conn);
	}

	return 0;	
}

