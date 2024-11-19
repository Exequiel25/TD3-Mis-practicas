// La aplicación cliente se conecta con un servidor (IP: 192.168.1.1, Puerto: 3000)
// Al recibir algo por teclado, envía por el socket "dato", lee la respuesta el socket y la muestra en pantalla.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
char a1[256], a2[256];
struct sockaddr_in a3 = {};
int a4, a5;
int main(int argc, char const *argv[])
{
    argv[1] = "3000";
    a3.sin_family = AF_INET;
    a3.sin_port = htons(atoi(argv[1]));
    inet_aton("192.168.1.1", &a3.sin_addr); // inet_aton convierte una dirección IPv4 en una dirección binaria
    a4 = socket(AF_INET, SOCK_STREAM, 0);
    connect(a4, (struct sockaddr *)&a3, sizeof(a3)); // Conecta el socket a la dirección del servidor
    while (1)
    {
        // Lee de la entrada estándar
        if ((read(STDIN_FILENO, a1, sizeof(a1))) > 0)
        {
            write(a4, "dato", 7); // Escribe en el socket
        }
        a5 = read(a4, a2, sizeof(a2)); // Lee del socket
        write(STDOUT_FILENO, a2, a5);
    }
    return 0;
}