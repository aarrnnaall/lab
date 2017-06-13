/*
 * tp1: Redireccionamiento
 *
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	char buff[500];
	int palabras = 0, oraciones = 0, especiales = 0;
	char *tok1, *tok2, *tok3, *sv1, *sv2, *sv3;
	char *seppal = " .", *sepor = ".", *sepesp = "\303";  
	
	while (read(0,buff,500) > 0){
		tok1 = strtok_r(buff, seppal, &sv1);
		while (tok1 != NULL){
			palabras++;
			tok1 = strtok_r(NULL, seppal, &sv1);}
		tok2 = strtok_r(buff, sepor, &sv2);	
		while (tok2 != NULL){
			oraciones++;
			tok2 = strtok_r(NULL, sepor, &sv2);}
		tok3 = strtok_r(buff, sepesp, &sv3);
		while (tok3 != NULL){
			especiales++;
                        tok3 = strtok_r(NULL, sepesp, &sv3);}
	}
	printf("Palabras: %d\n", palabras);
	printf("Oraciones: %d\n", oraciones);
	printf("Caracteres Especiales: %d\n", especiales);
    	
	return 0;
}
