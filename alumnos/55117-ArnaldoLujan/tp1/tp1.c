 /*
 * tp1: Redireccionamiento
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	int leido,fd=0,fd1=0,totalor=0,totalpal=0,totalesp=0;
	char buffer[500],*token="",*token1="",*token2="";
        const char a[2] = ".";
        const char b[3] = " .\n";
        const char c[2] = "\303";
        	
while ((leido = read(0,buffer,500)) > 0)
	{
           token = strtok(buffer, a);
           while(token != NULL )
             {
            token = strtok(NULL, a);
             if (token != NULL)	
               {	
              totalor++;
               }
             }
        }
fd = open("noticia1",O_RDONLY);	
while ((leido = read(fd,buffer,500)) > 0)
        {

           token1 = strtok(buffer, b);
           while(token1 != NULL )
             {
            token1 = strtok(NULL, b);
             if (token1 != NULL)
               {
              totalpal++;
               }
             }
        }
fd1 = open("noticia1",O_RDONLY); 
while ((leido = read(fd1,buffer,500)) > 0)
        {
           token2 = strtok(buffer, c);
           while(token2 != NULL )
             {
            token2 = strtok(NULL, c);
             if (token2 != NULL)
               {
              totalesp++;
               }
             }
        }
        printf("+Cantidad de Palabras: %d\n",totalpal);
	printf("+Cantidad de Oraciones: %d\n",totalor);
	printf("+Cantidad de Palabras Especiales: %d\n",totalesp);
	
	return 0;
}

