#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include<string.h>

int main(int argc, char **argv)
{
int pid, pid2, status, status2,nread,totalpal=0;
int hijo1[2],hijo2[2],padre[2],i,j;
char buffer[20],recibido[4],envio[4],*token="";
 
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
memset(buffer, hijo1[0], sizeof buffer);        
do {
        nread = read(hijo1[0], buffer, sizeof buffer);
                         token = strtok(buffer," .\n");
                         while(token != NULL )
                          {
                          token = strtok(NULL," .\n"); 
                           if (token != NULL)
                             {
                              totalpal++;
                             }
                          }
   
 } while (nread > 0);
printf("Cantidad de Palabras: ");
sprintf(envio,"%d",totalpal);
write(padre[1],envio,4);
close(hijo1[0]);
close(padre[1]);
return 0;
                }

if(pid2 == 0)//hijo2
        {
        close(hijo2[1]);
        close(hijo1[1]);
        close(padre[0]);
        close(hijo1[0]);
        close(padre[1]);
        close(1); 
        
open (argv[2],O_CREAT|O_WRONLY,0664);
memset(buffer, hijo2[0], sizeof buffer);
 do {
        nread = read(hijo2[0], buffer, sizeof buffer);
         for(i=0;i<20;i++)	
             {
              if (buffer[i]>='A' && buffer[i]>='Z')	
                  {
                   for(j=0;j<20;j++)	{
                                         buffer[j] += 32;
                                        }
                  }
                   else	{
                         for(j=0;j<20;j++)	{	
                                                 buffer[j] -= 32;
                                                }
                                                          
                        } 	   
             }   
                                
   } while (nread > 0);

write(STDOUT_FILENO, buffer,nread);

        close(1); 
        close(hijo2[0]);
        return 0;
        }
if ( pid >0 && pid2 > 0)//padre
        {
                        
           close(hijo1[0]);
           close(hijo2[0]);
           close(padre[1]);
memset(buffer, 0, sizeof buffer);
do {
        nread = read(0, buffer, 20);
            write(hijo1[1],buffer,nread);
            write(hijo2[1],buffer,nread);
    } while (nread > 0);
                        
                        close(hijo1[1]);
                        close(hijo2[1]);

                        wait(&status);
                        wait(&status2);
                        

read(padre[0],recibido,4); 
write(1,recibido,4);
printf("\n");
close(padre[0]);
        return 0 ;
        }
return 0;
}
