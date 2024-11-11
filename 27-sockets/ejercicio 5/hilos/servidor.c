/*
programa SOCKET SERVIDOR Stream (TCP) el servidor envia al socket
lo que recibe del socket y muestra en pantalla lo recibido en
el socket: Cliente:--> datos rx socket
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <pthread.h>

int des_socket, sck_server, rx_socket, largo, cont;
char buffer_rx[256];
struct sockaddr_in struct_direccion = {};
int SockEscucha, SockConexion;

void *handle_client(void *client_sock_ptr)
{
  int client_sock = *(int *)client_sock_ptr;
  free(client_sock_ptr);
  char buffer_rx[256];
  int rx_socket;

  send(client_sock, "Bienvenido al servidor\n", 23, 0);

  while ((rx_socket = read(client_sock, buffer_rx, sizeof(buffer_rx))) > 0)
  {                                             // lee del socket
    write(client_sock, buffer_rx, rx_socket);   // escribe en socket
    write(STDOUT_FILENO, "cliente:--> ", 12);   // escribe leyenda en pantalla
    write(STDOUT_FILENO, buffer_rx, rx_socket); // escribe lo leido del socket
  }

  close(client_sock);
  pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{

  if (argc != 2)
  {
    argv[1] = "2000";
  }

  //****************** 1 *******************//
  //-- socket(): Crear el socket -----------//
  SockEscucha = socket(AF_INET, SOCK_STREAM, 0);

  if ((SockEscucha) < 0)
  {
    printf("ERROR en funcion socket()\n");
    exit(-1);
  }

  printf("Paso 1: Servidor creo socket\n");

  //****************** 2 *******************//

  //-- preparar el address:port -------------//
  struct_direccion.sin_family = AF_INET;
  struct_direccion.sin_addr.s_addr = htonl(INADDR_ANY); // asigna una IP de la maquina
  struct_direccion.sin_port = htons(atoi(argv[1]));     // puerto

  //-- bind(): asociamos el socket a la direccion------//

  if (bind(SockEscucha, (struct sockaddr *)&struct_direccion, sizeof(struct sockaddr_in)) < 0)
  {
    printf("ERROR en funcion bind()\n");
    exit(-1);
  }

  printf("Paso 2: Asociar bind() \n");

  //****************** 3 *******************//
  //-- listen(): Permitir hasta 1 conexion pendiente --//

  if ((listen(SockEscucha, 1)) < 0)
  {
    printf("ERROR en funcion listen()\n");
    exit(-1);
  }

  printf("Paso 3: Permitir conexiones listen()\n");

  while (1)
  {

    //****************** 4 *******************//
    //-- accept(): se bloquea hasta que entre una conexion --//

    printf("Paso 4: Bloqueo hasta que entre conexion accept()\n");
    SockConexion = accept(SockEscucha, NULL, 0);

    if (SockConexion >= 0)
    {
      printf("Desbloqueo de accept, entro conexion: %d\n", SockConexion);

      pthread_t thread_id;
      int *client_sock_ptr = malloc(sizeof(int));
      *client_sock_ptr = SockConexion;

      if (pthread_create(&thread_id, NULL, handle_client, client_sock_ptr) != 0)
      {
        printf("Error en pthread_create()\n");
        close(SockConexion);
        free(client_sock_ptr);
      }
      else
      {
        pthread_detach(thread_id); // Detach the thread to handle cleanup automatically
      }
    }
    else
    {
      printf("Error en la conexion\n");
    }
  }

  //****************** 5 *******************//
  //------------cierrar la conexion --------//

  close(SockEscucha);

  return 0;
}