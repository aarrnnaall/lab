#include <errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "funciones.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

 
 void *servidor(void *sd1) {
 	

        char buffer[1024]; 
        char buffer_copy[1024];
        char recurso[100]; 
        char metodo[4];
        char nombre_archivo[50];
        char extension[7];
 	int leido,fd,sd2;
 	char *token;
 	 
     
     sd2=*((int*)sd1);
       
      if(sd1 != NULL){
     	free(sd1);//libera el espacio de memoria apuntado por sd1
     }
     	
        leido = read(sd2, buffer, sizeof buffer);
 
 	printf("%s \n", buffer);
 
 	strcpy(buffer_copy, buffer); 
    	
    	token = strtok(buffer_copy, " "); 
 	strcpy(metodo, token);
    	token = strtok(NULL, " ");
 	strcpy(recurso, token+1);
 
 	if ((strcmp(buffer, "") == 0)){
 write(sd2, "HTTP/1.1 500 INTERNAL SERVER ERROR\nContent-type: text/html\nContent-Length: 25\n\n500 INTERNAL SERVER ERROR", strlen("HTTP/1.1 500 INTERNAL SERVER ERROR\nContent-type: text/html\nContent-Length: 25\n\n500 INTERNAL SERVER ERROR"));
 	}else if (!(strncmp(metodo, "GET",3) == 0)){
 write(sd2, "HTTP/1.1 405 METHOD NOT ALLOWED\nContent-type: text/html\nContent-Length: 23\n\n405 METHOD NOT ALLOWED", strlen("HTTP/1.1 405 METHOD NOT ALLOWED\nContent-type: text/html\nContent-Length: 23\n\n405 METHOD NOT ALLOWED"));
 	}else if ((fd = open(recurso, O_RDONLY)) < 0){//achivo no encontrado 
 		switch(errno){
 			case 13:	
 write(sd2, "HTTP/1.1 403 FORBIDDEN\nContent-type: text/html\nContent-Length: 13\n\n403 FORBIDDEN", strlen("HTTP/1.1 403 FORBIDDEN\nContent-type: text/html\nContent-Length: 13\n\n403 FORBIDDEN"));
 				 
 				break;
 			case 2:
 write(sd2, "HTTP/1.1 404 NOT FOUND\nContent-type: text/html\nContent-Length: 13\n\n404 NOT FOUND", strlen("HTTP/1.1 404 NOT FOUND\nContent-type: text/html\nContent-Length: 13\n\n404 NOT FOUND"));
 				 
    				break;
 		}
 		close(fd);
 	}else{//encuentra el Archivo
 
 		strcpy(nombre_archivo, recurso);
 		token = strtok(nombre_archivo, ".");
 		token = strtok(NULL, ".");
 		strcpy(extension, token);
                
 		if(strcmp(extension, "jpg")==0){ 
write(sd2,"HTTP/1.0 200 Ok\r\nContent-Type: image/jpeg\r\n\r\n",strlen("HTTP/1.0 200 Ok\r\nContent-Type: image/jpeg\r\n\r\n"));
 		}else if(strcmp(extension, "png")==0){
write(sd2, "HTTP/1.0 200 Ok\r\nContent-Type: image/png\r\n\r\n",strlen("HTTP/1.0 200 Ok\r\nContent-Type: image/png\r\n\r\n"));
 		}else if(strcmp(extension, "pdf")==0){
write(sd2, "HTTP/1.0 200 Ok\r\nContent-Type: application/pdf\r\n\r\n", strlen("HTTP/1.0 200 Ok\r\nContent-Type: application/pdf\r\n\r\n"));
 		}else if(strcmp(extension, "html")==0){
write(sd2, "HTTP/1.0 200 Ok\r\nContent-Type: text/html\r\n\r\n", strlen("HTTP/1.0 200 Ok\r\nContent-Type: text/html\r\n\r\n"));
 		}else if(strcmp(extension, "gif")==0){
write(sd2, "HTTP/1.0 200 Ok\r\nContent-Type: image/gif\r\n\r\n", strlen("HTTP/1.0 200 Ok\r\nContent-Type: image/gif\r\n\r\n"));
 		}else{
write(sd2, "HTTP/1.0 200 Ok\r\nContent-Type: text/plain\r\n\r\n", strlen("HTTP/1.0 200 Ok\r\nContent-Type: text/plain\r\n\r\n"));
 		}
 
 		while((leido = read(fd, buffer_copy, sizeof buffer_copy)) != 0){
 			write(sd2, buffer_copy, leido);
 		}
 		close(fd);
 	}
 	close(sd2);
 	pthread_exit(NULL);
 	
 }
