#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/MI_FIFO"

int main()
{
    int fifo_d, leido;
    char buff[80];

    fifo_d = open(FIFO_PATH, O_RDONLY, 0);

    if (fifo_d == -1)
    {
        write(STDOUT_FILENO, "Error al abrir FIFO\n", sizeof("Error al abrir FIFO\n"));
        return -1;
    }
    else
    {
        write(STDOUT_FILENO, "Lector: FIFO abierta correctamente\n", sizeof("Lector: FIFO abierta correctamente\n"));
        leido = read(fifo_d, buff, sizeof(buff));
        if (leido == -1)
        {
            write(STDOUT_FILENO, "FIFO vacía\n", sizeof("FIFO vacía\n"));
        }
        else
        {
            write(STDOUT_FILENO, "Mensaje leido de FIFO: ", sizeof("Mensaje leido de FIFO: "));
            write(STDOUT_FILENO, buff, leido - 1);
            write(STDOUT_FILENO, "\n", sizeof("\n"));
        }
    }

    close(fifo_d);

    return 0;
}