/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define FRASE_A "INFORMACION IMPORTANTE A"
#define FRASE_B "INFORMACION IMPORTANTE B"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
   // manejador de la señal sigpipe
   printf ("SIGPIPE\n");
}

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);
   
   // creación tubería
   pipe(ipc);

   // creación proceso hijo y discriminación código
   switch (fork()){ 
      
      case 0:
	   // cerrar descriptor de lectura
	   close(ipc[0]);      
	   strncpy(buff, FRASE_A, sizeof(FRASE_A)); 
	   // escribimos la FRASE_A en la tubería
	   write(ipc[1], buff, sizeof(FRASE_A));
	   // cerramos el descriptor de escritura
	   close(ipc[1]);
	   exit(0);
      break;
      
      default:
      // creamos otro procesa hijo
      switch (fork()){ 
            
         case 0:
	    // cerramos descriptor lectura
            close(ipc[0]);               
            strncpy(buff, FRASE_B, sizeof(FRASE_B)); 
	    // escribimos
            write(ipc[1], buff,    sizeof(FRASE_B));
	    // cerramos descriptor escritura
            close(ipc[1]);
            exit(0);      
         break;
         
         default:
	    // cerramos el directorio escritura
            close(ipc[1]);
            int i;
            
            sleep(1);
            // leemos todo lo que haya en la tubería
            for(i=0; i<2; i++){
               leido = read(ipc[0], buff, sizeof(buff));
	       // si no hay bytes:
               if(leido < 1){
                  write (STDOUT_FILENO, "Padre, Error al leer tuberia\n", sizeof("Padre, Error al leer tuberia\n"));
               }else {
                  write (STDOUT_FILENO, "Padre, Leido de la tuberia \"", sizeof("Padre, Leido de la tuberia \""));
                  write (STDOUT_FILENO, buff, leido-1);
                  printf("\" por el proceso padre\n.");
               }
            }

	    // cerramos descriptor
            close(ipc[0]);
	    // esperamos a los procesos hijos
            wait(NULL);
            wait(NULL);
            exit(0);
         break;
      }
   }   
}
