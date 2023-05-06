/*
 * PARCIAL 1: programa para ser ejecutado en el proceso padre.
 *
 * Comando para compilar:
 *
 * 	gcc -c padre.c && gcc hijo.o padre.o -o padre
 *
 * Resuelto para practicar.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MENSAJE "HOLA HIJA MIA"

int hijo(int fd[2]);

int main(void)
{
	// Identificamos que el método de IPC es PIPE
	int fd[2];
	int pid;
	char tx_buffer[20] = MENSAJE;

	if (pipe(fd) == -1)
	{
		// no pudimos crear el PIPE
		perror("pipe");
		return -1;
	}

	if ((pid = fork()) == -1)
	{
		// no pudimos crear el proceso hijo
		perror("fork");
		return -1;
	}

	// codigo que ejecuta el hijo
	if (pid == 0)
	{
		// función en hijo.c (el que no tenemos acceso)
		hijo(fd);

		return 0;
	}
	// codigo que ejecuta el padre
	else
	{
		printf("Proceso Padre en ejecucion... \n");

		sleep(1);

		// **** RESOLUCION DEL EJERCICIO *******************************
		// Suponemos que el hijo cierra el extremo de escritura
		// Cerramos en el padre el extremo de lectura
		close(fd[0]);
		// debemos escribir en la tubería
		printf("Padre escribe en la tuberia... \n");
		write(fd[1], tx_buffer, strlen(tx_buffer) + 1);

		// *************************************************************

		wait(NULL);
		// como la persistencia de un PIPE es de proceso,
		// no interesa realmente cerrar el descriptor de escritura
		exit(0);
	}
}
