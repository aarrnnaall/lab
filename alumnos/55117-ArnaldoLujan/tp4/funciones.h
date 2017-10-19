#ifndef FUNCIONES_H
#define FUNCIONES_H

void Servidor(char *port);
void respuesta(int n);
void error(char *);
char *ruta;
int fd;
int  clients[10000];
#endif
