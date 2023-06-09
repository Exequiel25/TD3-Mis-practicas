/*
 * PARCIAL 1: programa para ser ejecutado en el proceso padre.
 *
 * Comando para compilar:
 *
 * 		gcc -c padre.c && gcc -O0 hijo.o padre.o -o padre

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int hijo(int fd[2], char *myfifo);

int main(void)
{
    int fd[2];
    int fd_fifo;
    int pid;
    char tx_buffer[20] = {"HOLA HIJO MIO\0"};
    char *myfifo = "/tmp/myfifo";

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return -1;
    }

    unlink(myfifo);

    if (mkfifo(myfifo, 0666) == -1)
    {
        perror("fifo");
        return -1;
    }

    if ((pid = fork()) == -1)
    {
        perror("fork");
        return -1;
    }

    // codigo que ejecuta el hijo

    if (pid == 0)
    {
        hijo(fd, myfifo);

        return 0;
    }

    // codigo que ejecuta el padre

    else
    {
        printf("Proceso Padre en ejecucion... \n");

        sleep(1);

        // **** ESCRIBIR CODIGO A PARTIR DE ESTA LINEA *****************
        // cerramos el descriptor de lectura del pipe
        // ya que solo escribimos
        close(fd[0]);
        // escribimos en el pipe
        write(fd[1], tx_buffer, strlen(tx_buffer));
        // cerramos el descriptor de escritura del pipe
        close(fd[1]);

        // *************************************************************

        wait(NULL);

        return 0;
    }
}
