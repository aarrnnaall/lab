/* *************************************************************** */
/*                          FUNCIONES                              */
/* *************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int calcular_palabras(char *linea, int longitud) {

    int i, palabra = 0;

    for (i=0; i<longitud; i++) {
        if (linea[i] == 32) {
            palabra++;
        }
    }

    return palabra;
}

int calcular_oraciones(char *linea, int longitud) {

    int i, oracion = 0;

    for (i=0; i<longitud; i++) {
        if (linea[i] == 10) {
            oracion++;
        }
    }

    return oracion;
}

int calcular_caracteres(char *linea, int longitud) {

    int i, j, caracter = 0;
    /* validos: espacio, numeros, letras mayusculas, letras minusculas */
    int validos[63] = {32,48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,
        79,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,
        111,112,113,114,115,116,117,118,119,120,121,122};

    for (i=0; i<longitud; i++) {
        for (j=0; j<sizeof j; j++) {
            if (linea[i] != validos[j]) {
                caracter++;
            }
        }
    }

    return caracter;
}

