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

int main(int argc, char **argv)
{
	int leido, cantidad = 0, oraciones = 0, caracters = 0;
	char buff[1000];
	char texto[1000];
	char texto2[1000];
	char s1[] = ".";
	char s2[] = " \n"; // \t para tabulacion 	
	char s3[]= "\303";
	char *palabras, *oracion, *caracteres;

	while((leido = read(0,buff,1000))> 0){
			
		write(1,buff,leido);
		strcpy(texto,buff);
		strcpy(texto2,texto);	

		palabras = strtok(buff,s2);
		while((palabras = strtok(NULL, s2)) != NULL){
			cantidad++;				
		}						
		
		oracion = strtok(texto,s1);
		while((oracion = strtok(NULL, s1)) != NULL){
			oraciones++;				
		}			
		
		caracteres = strtok(texto2,s3);
		while((caracteres = strtok(NULL, s3)) != NULL){
			caracters++;				
		}			
	}

	printf("cantidad de palabras: %d\n", cantidad);

	printf("cantidad de oraciones: %d\n", oraciones);
	
	printf("cabtidad de palabras con caracters especiales: %d\n", caracters);
	
	return 0;
}


	//no lo uso ya que el tp pide que sea cat noticia1 | ./tp1
	//archivo = open("./noticia1",O_RDONLY,0666);
	
	//por eso uso el descriptor 0 y la funcion cat que lee del teclado!

	//cantidad de palabras que lea hasta un espacio "" y ahi contar 1 
	//cantidad de oraiciones que lea hasta un \n y contar 1
	//ver lo de cantidad de palabras con caracteres especiales

	//leido2 = read(0,buff,500);
	

	//funciones para contar strlen(const char *s)	

	//strlen: retorna el numero de caracteres hasta el caracter no nulo, no lo incluye;
	//char s[14]= "hola mundo";
	//printf("s= %s\n", s);
	//printf("strlen(s) = %d\n", strlen(s));

	//strchr: retorna un puntero a partir del caracter encontrado. si no se ha encontrado
	//el caracter "c", retorna un puntero null
	//char s[30]= "holamundo holaaa holaa";
	//char d = ' ';
	//printf("s= %s\t", s);
	//printf("d= %c\n", d);
	//printf("strchr= %s\n", strchr(s,d));

	//strcspn: retorna el numero de caracteres leidos de la subcadena hasta que halla alguno
	//de los caracteres de s2. el caracter nulo no se cuenta
	//char s1[13]= "hola mundo";
	//char s2[5] = " ";
	//printf("s1= %s\t", s1);
	//printf("s2= %s\n", s2);
	//printf("strcspn(s1,s2)= %d\n", strcspn(s1,s2));
	
	//strpbrk
	//strrchr
	//strstr

	//strtok: la primera llamada a strtok determina la cadena a romper, retonarndo el puntero
	//al comienzo del primer token. Si se recorrio la cadena s1 sin haber encontrado un
	//delimitador, y aun no se ha obtenido el primer token, entonces retornara un puntero
	//nulo
	//posteriores llamadas retornaran mas tokens. Si ya no encuentra mas delimitadores,
	//entonces retornara todos los caracteres desde el ultimo delimitador para hacer el
	//ultimo token. Si ya se retorno el ultimo token, entonces retornara un puntero
	//nulo con demas llamadas a la funcion-


	//a=5, e=3, i= 11, o=9
	/*while((leido = read(0,buff,1000))> 0){
		
		write(1,buff,leido);
		oracion = strtok(buff,s1);
		while((oracion = strtok(NULL, s1)) != NULL){
			oraciones++;				
		}			
	}*/	
	
	/*while((leido = read(0,buff,1000))> 0){
		
		write(1,buff,leido);
		caracteres = strtok(buff,s3);
		while((caracteres = strtok(NULL, s3)) != NULL){
			caracters++;				
		}			
	}*/	
	
/*	char s1[50]= "Esto es. Un ejemplo para. Usar la funcion strtok()";
	char s3[] = ".";
	char *ptr;
	printf("s1= %s\t", s1);
	ptr = strtok(s1,s3); //primer llamado
	printf("\n%s\n",ptr);
	while( (ptr = strtok(NULL, s3)) != NULL){ //posteriores llamados
		printf("%s\n", ptr);
		oraciones++;		
	}
*/

