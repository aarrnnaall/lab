#include <unistd.h>
#include <stdio.h>
#include <string.h>
int
main (int argc, char **argv)
{
    char buffer[1];
	char anterior[1] = {'1'};
	int readed = 1, palabras = 0, oraciones = 0, espacios = 0;

    while ((readed = read(0, buffer, 1))) {
    write(1, "El buffer es: ", 14);
    write(1, buffer, 1);
    write(1, "\n", 1);   
    write(1, "El anterior es: ", 16);
    write(1, anterior, 1);
    write(1, "\n", 1);
        //Cuenta las palabras    
		if (*buffer == ' ' || *buffer == '.' || *buffer == ',' || *buffer == '(' || *buffer == ')' || *buffer == '\n') {
			palabras++;
			if (*anterior == ' ' || *anterior == '.' || *anterior == ',' || *anterior == '(' || *anterior == ')' || *anterior == '\n' || *anterior == '1') {
				palabras--;
			}
		}
        //Cuenta las oraciones
		if (*buffer == '.') {
			oraciones++;
			if (*anterior == '.' || *anterior == '1') {
				oraciones--;
			}
		}

        //Cuenta los espacios
    	if (*buffer == '\n' || *buffer == ' ') {
			espacios++;
		}	
    *anterior = *buffer;

    }
    printf("Cantidad de palabras: %d\n", palabras);
    printf("Cantidad de oraciones: %d\n", oraciones);
    printf("Cantidad de espacios: %d\n", espacios); 
    //Imprimo las estadisticas
	return (0);	
}
