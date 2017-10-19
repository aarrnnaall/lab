#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>
#include "funciones.h"
#include <netinet/in.h>

//char *ruta;
//int fd;
//int  clients[10000];

void Servidor(char *port)
{
        struct addrinfo hints, *res, *p;
        //getaddrinfo 
        memset (&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        if (getaddrinfo( NULL, port, &hints, &res) != 0)
        {
                perror ("Error en getaddrinfo()");
                exit(1);
        }
        //socket and bind
        for (p = res ; p!=NULL ;p=p->ai_next)
        {
                fd = socket (p->ai_family, p->ai_socktype, 0);
                if (fd == -1){ continue;}
                if (bind(fd, p->ai_addr, p->ai_addrlen) == 0){ break;}
        }
        if (p==NULL)
        {
                perror ("Error en socket() o bind()");
                exit(1);
        }

        freeaddrinfo(res);

        //Escucha las conexiones entrantes 
        if ( listen (fd, 1000000) != 0 )
        {
                perror("Error en listen() ");
                exit(1);}
}
//funcion respuesta 
void respuesta(int n)
{
	char mesg[1024000], *reqline[3], datosenviar[1024], path[1024000];
	int rcvd, fd, leidobytes;
        char *Internal_error="Internal error";
        int codigo = 500;
        int codigo1= 403;
        char *Forbidden="Forbidden";
        char *http = "HTTP/1.1";
        memset( (void*)mesg, (int)'\0', 1024000 );
        char post[]="Metodo usado POST: ";
        rcvd=recv(clients[n], mesg, 1024000, 0);
        struct stat baf;
        int perm=baf.st_mode;//son los permisos del archivo
	int tam=baf.st_size;//es el tamaño del archivo
        if (rcvd<0)    // Recibe Error
		fprintf(stderr,("Error de recv() \n"));
	else if (rcvd==0)    // Recibe socket cerrado
		fprintf(stderr,"Cliente Desconectado inesperado.\n");
	else    // mensaje recibido
	{
		printf("%s", mesg);
		reqline[0] = strtok (mesg, " \t\n");//metodo
		reqline[1] = strtok (NULL, " \t");//nombre del archivo
                reqline[2] = strtok (NULL, " \t\n");//nombre de la extencion
                if(strcmp(reqline[0],"POST")==0)//SI es el Metodo POST
                                {
                write(clients[n],post,sizeof(post));
                snprintf(datosenviar,sizeof(datosenviar), "%s %d %s \r\n\r\n",http,codigo,Internal_error);
                write(clients[n],datosenviar,sizeof(datosenviar));//muestra el mensaje de estado 500
                                
                                }

                if ( strncmp(reqline[0], "GET\0", 4)==0 )//SI es el Metodo GET
		{
			
			if ( strncmp( reqline[2], "HTTP/1.1", 8)==0 )
			{
				if ( strncmp(reqline[1], "/\0", 2)==0 )
					reqline[1] = "";        

				strcpy(path, ruta);
				strcpy(&path[strlen(ruta)], reqline[1]);
				printf("file: %s\n", path);

				if ( (fd=open(path, O_RDONLY,0664))!=-1 )//Archivo Encontrado
				{
					send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
					while ( (leidobytes=read(fd, datosenviar, 1024))>0 )//muestra el mensaje de estado 200
						write (clients[n], datosenviar, leidobytes);
				
                                }
				else{//Archivo no Encontrado	
                                if(perm<0)//si no se tiene permisos
                                                {
                   snprintf(datosenviar,sizeof(datosenviar), "%s %d %s \r\n\r\n",http,codigo1,Forbidden);
                                 write(clients[n],datosenviar,sizeof(datosenviar));//muestra el mensaje de estado 403
                                 //agregar content-length y content-type
                                    if((strcmp(reqline[2],"html"))==0)
                                        {
                                          dprintf(clients[n],"Content-Type: text/%s",reqline[2]);
                                        }
                                            dprintf(clients[n],"\n");
                                            dprintf(clients[n],"Content-Length: %d",tam);
                                            dprintf(clients[n],"\n\n");
                                               
                                                }
                                        else{
                                write(clients[n], "HTTP/1.0 404 Not Found\n", 23);//muestra el mensaje de estado 404
                                            }
				}
                         }
		}
	}

	//Cerrando SOCKET
	shutdown (clients[n], SHUT_RDWR);        
	close(clients[n]);
	clients[n]=-1;
}
