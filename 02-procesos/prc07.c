/*
 * Ejercicio 7 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i = 2;

	do {
		pid = fork();		
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
		printf ("Variable de control i = %d\n", i);
	} while (i-- > 0);

	// Ejecute pstree en otra consola	
	sleep(30); 

	exit(0);

}
