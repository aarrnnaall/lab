#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>


int main(int argc, char **argv)
{
int pid, pid2, status, status2,leido,totalpal=0;
int hijo1[2],hijo2[2],padre[2],i,j;
char buffer[20],recibido[4],envio[4],*token="";
const char a[3] = " .\n";
const char b[2] = "\303";
 pipe(hijo1);
 pipe(hijo2);
 pipe(padre);
  
    pid=fork();
if(pid > 0){
    pid2=fork();
           }else{//hijo1	
                close(hijo1[1]);
                close(padre[0]);
                close(hijo2[0]);
                close(hijo2[1]);

                     while((leido=read(hijo1[0],buffer,sizeof buffer))>0)//lee el buffer hasta que este vacio
                     {
                        token = strtok(buffer, a);
                         while(token != NULL )
                          {
                          token = strtok(NULL, a);
                           if (token != NULL)	
                            {	
                             totalpal++;
                            }
                          }
	             }

sprintf(envio,"%d",totalpal);
write(padre[1],envio,4);
close(hijo1[0]);
close(padre[1]);
return 0;
                }

if(pid2 == 0)
        {
        close (hijo2[1]);
        close(hijo1[1]);
        close(padre[0]);
        close(hijo1[0]);
        close(padre[1]);
        close(1); 
        open (argv[2],O_CREAT|O_WRONLY,0777);
                        
           while((leido=read(hijo2[0],buffer,sizeof buffer))>0)
                {
                        token = strtok(buffer, b);
                           while(token != NULL )
                                {
                                token = strtok(NULL, b);
                                  if (token != NULL)	
                                   {	
                                      if(buffer[i] >= 'A' && buffer[i] <= 'Z')
                                              {
                                                 for(j=0;j<20;j++)
                                                       {
                                                        buffer[j] = toupper(buffer[j]);
                                                       }
	                                      }	                           
                                   }
                                }
                        
                        write(STDOUT_FILENO, buffer,leido);
                }
        close(1); 
        close(hijo2[0]);
        return 0;
        }
if ( pid >0 && pid2 > 0)//padre
        {
                        
           close(hijo1[0]);
           close(hijo2[0]);
           close(padre[1]);

                         while((leido=read(0,buffer,20))>0)
                                {
                                  write(hijo1[1],buffer,leido);// escribe lo leido de noticia en el pipe para el primer hijo
                                  write(hijo2[1],buffer,leido);// escribe lo leido de noticia en el pipe para el segundo hijo
                                }
                        close(hijo1[1]);
                        close(hijo2[1]);

                        wait(&status);//espera que termine el proceso hijo1
                        wait(&status2);// espera que termine el proceso hijo2

                        read(padre[0],recibido,4); //lee la informacion enviada por el pipe hijo1padre y lo guarda en el buffer lectura
                        
                        write(1,recibido,5);// muestra por pantalla el contenido del buffer lectura
                        printf("Cantidad de palabras: ");
                        close(padre[0]);
        return 0 ;
        }
return 0;
}
