/*
 * Ejercicio 2 de TP PIPE
 * 
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   // Crea la tubería
   if (pipe(ipc) == -1)
      exit(-1);

   // Crea el hijo y a su vez discrimina el código del padre y del hijo
   switch (fork()){
      
      case 0:
         printf("Hijo escribiendo en tuberia, pid %d... \n", getpid());
	 // cerramos el descriptor de lectura
         // close(ipc[1]); // línea incorrecta
	 close(ipc[0]);
         strncpy(buff, DATA, sizeof(DATA)); 
	 // escribimos en la tubería
         write(ipc[1], buff, sizeof(DATA));
	 // fin del hijo
         exit(0);
         
      default:
         printf("Padre leyendo tuberia, pid %d... \n", getpid());
	 // leemos la tubería
         leido = read(ipc[0], buff, sizeof(buff));
         if(leido < 1){
            // escribimos en la tubería
	    write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
         }else {
	    // escribimos en la tubería
	    write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
            // escribimos en la tubería
	    write (STDOUT_FILENO, buff, leido-1);
            printf("\" por el proceso padre.\n");
         }
         wait(NULL);

         exit(0);
   }
}
