#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int
main(int argc, char **argv)
{
    char buff[1];
    char ant[1] = {'0'};
    char aux[10];
    int leido, palabras = 0, fd, fd2, i, flag;
    //siempre definir los pipes antes del fork 
    //para poder compartir el espacio de memoria
    //son 3 pipes, dos para que el padre lea,
    // y escriba en dos pipes dirigidos a ambos hijos,
    //  el tercero es para la respuesta del primero.
    int pfd1[2];
    int pfd2[2];
    int pfd3[2];
    pipe(pfd1);
    pipe(pfd2);
    pipe(pfd3);
    pid_t p1, p2;
    
    
    //Leer argumentos pasados
    int iflag = 0;
    char *ivalue = NULL;
    int oflag = 0;
    char *ovalue = NULL;
    int opt;

    opterr = 0;

    while ((opt = getopt (argc, argv, "i:o:")) != -1) {
        switch(opt)
        {
            case 'i':
                iflag = 1;
                ivalue = optarg;
                break;

            case 'o':
                oflag = 1;
                ovalue = optarg;
                break;

            case '?':
                if (optopt == 'o')
                    fprintf (stderr, "La opcion -%o requiere un argumento\n", optopt);
                else if (isprint (optopt))//checkea que un caracter pueda ser impreso
                    fprintf (stderr, "Opcion desconocida -%c.\n", optopt);
                break;

            default:
                abort ();
        }
    }
     printf("iflag = %d, ivalue = %s,  oflag = %d, ovalue = %s\n", iflag, ivalue, oflag, ovalue);
    //Fin de lectura de argumentos
    
    switch(p1 = fork()) {

        case 0:
            //Leo del pipe lo que mando el padre
            //y lo muestro por pantalla
            //cierro pipe de escritura
            close(pfd1[1]);
            close(pfd2[1]);
            while((leido = read(pfd1[0], buff, 1)) > 0) {
                //Cuenta las palabras    
                if (*buff == ' ' || *buff == '.' || *buff == ',' || *buff == '(' || *buff == ')' || *buff == '-' || *buff == '\n') {
                    palabras++;
                        if (*ant == ' ' || *ant == '.' || *ant == ',' || *ant == '(' || *ant == ')' || *ant == '-' || *ant == '\n' || *ant == '1') {
                            palabras--;
                        }
                }
                *ant = *buff;
            }
            //una vez leido cierro pipe de lectura
            close(pfd1[0]);
            close(pfd2[0]);
            close(pfd3[0]);

            sprintf(aux, "%d", palabras);
            write(pfd3[1],aux, 10);
            close(pfd3[1]);
            return 1;
            break;

        case -1:
            perror("fork()");
            return -1;
            break;

        default:

            switch(p2 = fork()) {

                case 0:
                    close(pfd1[1]);
                    close(pfd2[1]);
                    close(pfd3[1]);

                    //Convertir minusculas a mayusculas 
                    char str[1];
                    //int i, fd, flag;
                    //abro un archivo para guardar la salida del segundo hijo
                    fd = open(ovalue, O_RDWR|O_CREAT, 0666);
                   
                    while((leido = read(pfd2[0], str, 1)) > 0) {
                        if(str[0] >= 65 && str[0] <= 90) {
                            flag = 1;
                        }

                        if(*str == ' ' || *str == '\n') {
                            flag = 0;
                        }

                        if(str[0]>=97 && str[0]<=122 && flag == 1) {
                            str[0]=str[0] - 32;
                        }

                        write(fd, str, 1);
                    }
                    //fin de conversion
                    close(pfd1[0]);
                    close(pfd2[0]);
                    close(pfd3[0]);    
                    return 1;
                    break;

                case -1:
                    perror("fork()");
                    return -1;
                    break;

                default:
                     //determinar si la entrada es estandar o a traves de un archivo
                    if(iflag) {
                        fd2 = open(ivalue, O_RDONLY, 0666);
                    }
                    else {
                        fd2 = 0;
                    }
                    //Escribo a ambos hijos en el pipe
                    close(pfd1[0]);
                    close(pfd2[0]);
                    while((leido = read(fd2, buff, 1)) > 0) {
                        write(pfd1[1], buff, 1);
                        write(pfd2[1], buff, 1);
                    }
                    close(pfd1[1]);
                    close(pfd2[1]);
                    close(pfd3[1]);
                    read(pfd3[0], aux, sizeof aux);
                    printf("Hay %s palabras\n", aux); 
                    close(pfd3[0]);
            }//Fin del segundo switch
            return 0;
            break;
    }//Fin del primer switch
}
