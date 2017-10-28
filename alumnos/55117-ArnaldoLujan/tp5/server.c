#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <string.h>
#include "funciones.h"
#include <pthread.h>	

 pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
 
 int main(int argc, char **argv)
 {
 	struct sockaddr_in hints = {};
 	int fd, sd1, *sd2;
        char puerto[6];
        char *ruta;
        pthread_t tid;	
  	fd = socket(PF_INET, SOCK_STREAM, 0);
 
 	if (fd == -1) perror("Error socket()");

ruta = getenv("PWD");
strcpy(puerto,"8000");

        //Imprime por pantalla el Nro. del puesto y el directorio
printf("El Servidor se inicio en el puesto Nro. %s%s%s con un directorio raiz %s%s%s\n","\033[92m",puerto,"\033[0m","\033[92m",ruta,"\033[0m\n"); 		 

        hints.sin_family= AF_INET;
        hints.sin_port = htons(8000);//puerto
 	inet_pton(AF_INET, "localhost", &hints.sin_addr);//direccion
        int valor=10000;
        setsockopt(fd,SOL_SOCKET, SO_REUSEADDR,&valor,sizeof(valor));
        
 	if (bind(fd, (struct sockaddr *) &hints , sizeof (hints)) < 0) perror("Error bind()");
 
 	if (listen(fd, 5) < 0) perror("Error listen()");
 		 
 	while ( (sd1 = accept(fd, NULL, 0)) > 0) {
 	              if((sd2=malloc(sizeof (int))) == NULL) perror("malloc");
 	                 *sd2=sd1;
                      if ((pthread_create(&tid,NULL,&servidor,(void *)sd2))!=0) perror("pthread");
 	                                         }
    pthread_exit(NULL);
 	
 }
 
