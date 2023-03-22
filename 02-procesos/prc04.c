/*
 * Ejercicio 4 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();
	if (pid == 0) {
		printf("Soy el hijo, mi pid es %d y el de papa es %d\n", getpid(), getppid());
	}
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

	// Ejecute pstree en otra consola	
	sleep(30); 

	exit(0);

}
