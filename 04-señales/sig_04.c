#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

int main ()
{
   int pid[3];
   int i = 0;

   printf("Soy el padre, mi PID = %d\n", getpid());
  // creamos los tres hijos que ejecuten un bucle infinito 
   do {
   	pid[i] = fork();
	if (pid[i] == 0) {
	   printf ("Soy el hijo, mi pid es %d y el pid de papa es %d\n", getpid(),getppid());
	   while(true);
	}
   } while (pid[i] != 0 && i++ < 2);
   
   // esperamos un poco antes de finalizar los procesos
   sleep(5);

   // enviamos la señal SIGKILL a cada proceso hijo
   // y esperamos que los mismos terminen
   for (int i=0; i<3; i++) {
	   kill(pid[i], SIGKILL);
	   waitpid(pid[i], NULL, 0);
	   printf("Proceso hijo pid=%d, finalizado\n", pid[i]);
   }

   printf("Proceso padre finalizado\n");

   exit(0);
}
