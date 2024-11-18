#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define MENSAJE "Mensaje para proceso B"
#define FIFO_PATH "/tmp/MI_FIFO"

int main()
{
    int err, fifo_d;

    err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.

    if (err == -1)
    {
        write(STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
    }
    else
    {
        write(STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
    }

    fifo_d = open(FIFO_PATH, O_WRONLY, 0);

    if (fifo_d == -1)
    {
        write(STDOUT_FILENO, "Error al abrir FIFO\n", sizeof("Error al abrir FIFO\n"));
        return -1;
    }
    else
    {
        write(STDOUT_FILENO, "Escritor: FIFO abierta correctamente\n", sizeof("Escritor: FIFO abierta correctamente\n"));
        write(fifo_d, MENSAJE, sizeof(MENSAJE));
        write(STDOUT_FILENO, "Mensaje escrito en FIFO\n", sizeof("Mensaje escrito en FIFO\n"));
    }

    close(fifo_d);

    return 0;
}