/*
 * tp1: Redireccionamiento
 *
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 60000


int main(int argc,  char *argv[])
{
   char buffer[SIZE],texto[SIZE];
	memset(buffer,0, sizeof(buffer));
 	char *palabras,*oraciones,*especiales;
			
	int palabrasCount = 0;
	int oracionesCount = 0;
	int especialesCount = 0;
	
	int leido;
	leido = read(STDIN_FILENO, buffer, sizeof buffer);
	write(STDOUT_FILENO, buffer, leido);
	
		strcpy(texto,buffer);
		palabras=strtok(texto, " ,-"); 
		while (palabras){
	      palabrasCount++;
			palabras=strtok(NULL," ");
		}
	
   	strcpy(texto,buffer);
		oraciones=strtok(texto, "."); 
		while (oraciones){
	      oracionesCount++;
			oraciones=strtok(NULL,".");
		}
		
   	strcpy(texto,buffer);
		especiales=strtok(texto, "áéíóúüÁÉÍÓÚÜ()"); 
		while (especiales){
	      especialesCount++;
			especiales=strtok(NULL,"áéíóúüÁÉÍÓÚÜ()");
		}
	
		printf("Total de palabras: %d\n",palabrasCount);
	   printf("Total de oraciones: %d\n",oracionesCount);
	   printf("Total de caracteres especiales: %d\n",especialesCount);

	return 0;
}
