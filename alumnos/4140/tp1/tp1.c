/*
 * TP1: Redireccionamiento
 * Crear una aplicación que procese un archivo por entrada estándar y muestre el resultado por la salida estándar.
 * La aplicación deberá imprimir una serie de estadísticas como:
 *                                                              - cantidad de palabras
 *                                                              - cantidad de oraciones
 *                                                              - cantidad de palabras con caracters especiales
 *
 * Modo de uso: $ cat noticia1 | ./tp1
 *
 * 
 */

#include <unistd.h>
#include <stdio.h>

#include "funciones.h"

int main(int argc, char **argv) {

    char buffer[100];
    int leido, palabra=0, oracion=0, caracter=0;

    while ((leido = read(STDIN_FILENO, buffer, sizeof buffer)) > 0) {
        palabra  += calcular_palabras(buffer, leido);
        oracion  += calcular_oraciones(buffer, leido);
        caracter += calcular_oraciones(buffer, leido);
    }

    printf("Cantidad de palabras: %d\n", palabra);                                  /* 226 palabras (228) */
    printf("Cantidad de oraciones: %d\n", oracion);                                 /* 23 oraciones (20) */
    printf("Cantidad de palabras con caracteres especiales: %d\n", caracter);       /* 23 caracteres (19) */

	return 0;
}
