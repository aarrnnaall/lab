/*
 * tp1: Redireccionamiento
 *
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	int i,oraciones=0,palabras=0,especiales=0;
	char buf[10];
	
	while (read(0,buf,10) > 0)
	{
		for(i=0;i<=10;i++)
		{
			if (buf[i] == '.' && buf[i-1] != '.' && buf[i-2] != '.')
			{
				oraciones ++;
			}

			if (buf[i] == ' ' || buf[i] == '.')
			{
				palabras ++;
			}

			if (buf[i] == '\303')
			{
				especiales ++;
			}

		}

	}
	
	//Mostrar estadisticas

	printf("ESTADISTICAS:\n");
	printf("-Palabras: %d\n",palabras);
	printf("-Oraciones: %d\n",oraciones);
	printf("-Especiales: %d\n",especiales);
	
	return 0;
}

