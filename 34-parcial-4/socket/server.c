// • Los datos recibidos por el socket los reenvía al socket cliente y los muestra en pantalla.
// • Puede conectarse con varios clientes en simultaneo utilizando hijos.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

char a2[256];
struct sockaddr_in st_dir = {};
int a1, a5, a6, a3;

int main(int argc, char const *argv[])
{
    argv[1] = "3000";

    st_dir.sin_family = AF_INET;                // Set the address family
    st_dir.sin_addr.s_addr = htonl(INADDR_ANY); // Set the address to any interface
    st_dir.sin_port = htons(atoi(argv[1]));     // Set the port

    a5 = socket(AF_INET, SOCK_STREAM, 0); // Create the socket STREAM

    bind(a5, (struct sockaddr *)&st_dir, sizeof(st_dir)); // Bind the socket to the address

    listen(a5, 1); // Listen for connections (allow only 1)

    while (1)
    {
        a6 = accept(a5, NULL, 0); // Accept the connection
        a3 = fork();              // Create a new process
        if (a3 == 0)
        {
            // Child process
            while ((a1 = read(a6, a2, sizeof(a2))))
            {
                // Read until there is no more data
                write(a6, a2, a1);            // Write the data back
                write(STDOUT_FILENO, a2, a1); // Write the data to the console
            }
        }
    }

    return 0;
}