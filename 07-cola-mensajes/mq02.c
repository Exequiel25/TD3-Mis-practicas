/*
 * Ejercicio 2 del TP de Cola de mensajes
 * y ejercicio 4
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3"

int err, leido;
char buff[1024];
mqd_t mqd;
struct mq_attr attr, attr_rcv;

void sig_user1(int a)
{

   err = mq_close(mqd);
   if ((err < 0))
   {
      write(STDOUT_FILENO, "error en mq_close()\n", sizeof("error en mq_close()\n"));
      exit(-1);
   }
   write(STDOUT_FILENO, "Cola de mensajes cerrada\n", sizeof("Cola de mensajes cerrada\n"));

   err = mq_unlink(MQ_PATH);
   if (err == -1)
   {
      write(STDOUT_FILENO, "error en mq_unlink()\n", sizeof("error en mq_unlink()\n"));
      exit(-1);
   }
   write(STDOUT_FILENO, "Cola de mensajes eliminada\n", sizeof("Cola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "Terminando proceso...\n", sizeof("Terminando proceso...\n"));

   exit(0);
}

int main()
{
   mq_unlink(MQ_PATH);

   // manejador de la señal SIGUSR1
   signal(SIGUSR1, sig_user1);

   // muestra el PID
   printf("Mi pid es %d\n", getpid());

   // determinamos el tamaño de los mensajes
   attr.mq_msgsize = sizeof(buff);
   // y de la cola de mensajes
   attr.mq_maxmsg = 8;

   // abrimos la cola de mensajes
   // establecemos permisos de escritura y lectura, pero no ejecución
   // El problema con la siguiente linea es que abre la cola de mensajes
   // para solo lectura, por lo que no se puede enviar mensajes
   // mqd = mq_open(MQ_PATH, O_RDONLY | O_CREAT, 0666, &attr);

   // Ejercicio 2: abrir solo escritura
   // mqd = mq_open(MQ_PATH, O_WRONLY | O_CREAT, 0666, &attr);
   // Ejercicio 4: abrir modo no bloqueante
   mqd = mq_open(MQ_PATH, O_WRONLY | O_CREAT | O_NONBLOCK, 0666, &attr);

   if (mqd < 0)
   {
      // si no se pudo abrir la cola de mensajes
      printf("error en mq_open()\n");
      exit(-1);
   }

   printf("Cola de mensajes creada\n");

   while (1)
   {

      // enviamos un mensaje
      err = mq_send(mqd, MENSAJE, strlen(MENSAJE) + 1, 1); // strlen nos da la longitud de una cadena
      if (err == -1)
      {
         // si no se pudo enviar el mensaje
         printf("error en mq_send()\n");
         exit(-1);
      }

      printf("Mensaje enviado (%d)\n", err);

      sleep(1);
   }

   exit(0);
}
