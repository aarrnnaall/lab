#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/shm.h> 
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>

int buscar(const char *palabra,const char *frase){//funcion para buscar palabra 
	const int fr_size = strlen(frase),pal_size = strlen(palabra);
	int cantidad = 0, letra = 0;
  	for (int i=0;i<fr_size;i++){
  		if (frase[i] == palabra[0]){
			for (int j=0;j<pal_size;j++){
				if (frase[i+j] == palabra[j]){
					letra++;
				}
			}

			if (letra == pal_size){
				cantidad++;
			}

			letra = 0;
		}
	}
return cantidad;
}
int contar(const char *frase){//funcion para contar palabras
	int cantidad = 0;
	for (int i=0;i<=1800;i++){
		if (frase[i] == ' ' || frase[i] == '.'){
			cantidad++;
		}
	}
return cantidad;
}
int main (int argc, char **argv)
 {
char *archivo = NULL,*mcomp,*pM=NULL;
char *pM2=NULL;
int pid2,mcompid2,status2;
char *mcomp2;
int *mostrar;
int op,fd;
//int i;
int contador,leido;
int pid,mcompid,status;
sem_t *padre,*hijo1,*hijo2;

while ((op = getopt (argc, argv, "i:")) != -1)
     switch (op)
       {
       case 'i':
         archivo = optarg;
         fd = open(archivo,O_RDONLY);
         break;
       case ':':
	/*OPCION SIN ARGUMENTOS*/
	fprintf(stderr,"%s: La opcion '-%c' requiere argumentos\n",argv[0],optopt);
	return -1;
	break;
       case '?':
	default:
	/*OPCION NO VALIDA*/
	fprintf(stderr,"%s: La opcion '-%c' es invalida\n",argv[0],optopt);
	return -1;
	break;
       	}

/*INICIALIZACION DE SEMAFOROS*/
        hijo1 = mmap(NULL,(sizeof(sem_t)+sizeof(int)),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
        hijo2 = mmap(NULL,(sizeof(sem_t)+sizeof(int)),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
        padre = mmap(NULL,(sizeof(sem_t)+sizeof(int)),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);

        mostrar = mmap(NULL,(sizeof(int)),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
        *mostrar = 0;

        sem_init(hijo1,1,0);
        sem_init(hijo2,1,0);
        sem_init(padre,1,1);


mcompid = shmget(1315511,1024,0664|IPC_CREAT);
mcomp = (char *)mmap (0, sizeof &mcomp, PROT_READ, MAP_SHARED, fd, 0);
mcompid2 = shmget(1315512,1024,0664|IPC_CREAT);
mcomp2 = (char *)mmap (0, sizeof &mcomp2, PROT_READ, MAP_SHARED, fd, 0);
close(fd);
if((pid = fork())>0){	
pid2=fork();
}
if(pid==0) { //El hijo1
             puts("Soy el hijo1");
             pM = shmat(mcompid,(void *)0,0); //Asociacion
             strcpy(pM,mcomp); 
/*for( i = 0; i <= strlen(pM) ; i++)
    {

        if(pM[i] == ' ' && pM[i+1] != ' ')
        {
           contador ++;
        }
    }*/
while(*mostrar == 0){        		
sem_wait(hijo1);
contador = contar(pM);
sem_post(hijo2);
	             }	
printf("Cantidad de palabras del TEXTO: %d\n",contador);

}	                               

if(pid2==0)	{	
puts("Soy el hijo2");
pM2 = shmat(mcompid2,(void *)0,0); //Asociacion
strcpy(pM2,mcomp2);
while(1)	{
sem_wait(hijo2);
printf("CANTIDAD DE PALABRAS DEL CONJUNTO DADO:\n");
printf("Hypertext: %d\n",buscar("Hypertext",pM2));
printf("protocol: %d\n",buscar("protocol",pM2));
printf("HTTP: %d\n",buscar("HTTP",pM2));
printf("MIME: %d\n",buscar("MIME",pM2));
printf("gateway %d\n",buscar("gateway",pM2));
printf("URL: %d\n",buscar("URL",pM2));
printf("URI: %d\n",buscar("URI",pM2));
sem_post(padre);
	}
}

if ( pid > 0 && pid2 >0)//padre
		{
            
            while ((leido = read(fd,pM,1800)) > 0){
                        sem_wait(padre);
                        sem_post(hijo1);
                }


                sem_wait(padre);

                *mostrar = 1;


                sem_post(hijo1);
            
            wait(&status);
            puts("Soy el padre");
            pM = shmat(mcompid,NULL,0); //Asociacion
            shmdt(&pM); //Desasociacion
            shmctl(mcompid,IPC_RMID,NULL);
            wait(&status2);
            pM2 = shmat(mcompid2,NULL,0); //Asociacion
            shmdt(&pM2); //Desasociacion
            shmctl(mcompid2,IPC_RMID,NULL);
 
            

                 }
return 0;	
	}    

	
