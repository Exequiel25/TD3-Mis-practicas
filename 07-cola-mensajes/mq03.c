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

   // manejador de la señal SIGUSR1
   signal(SIGUSR1, sig_user1);

   // muestra el PID
   printf("Mi pid es %d\n", getpid());

   // abrimos la cola de mensajes
   // En este caso, la abrimos para lectura
   // Ejercicio 2: abrir solo lectura
   // mqd = mq_open(MQ_PATH, O_RDONLY);
   // Ejericio 4: modo no bloqueante
   mqd = mq_open(MQ_PATH, O_RDONLY | O_NONBLOCK);

   if (mqd < 0)
   {
      // si no se pudo abrir la cola de mensajes
      printf("error en mq_open()\n");
      exit(-1);
   }

   printf("Cola de mensajes abierta\n");

   while (1)
   {

      // Se leen parametros de la cola de mensajes
      if (mq_getattr(mqd, &attr_rcv) == -1)
      {
         printf("error en mq_getattr()\n");
         exit(-1);
      }

      printf("Nro max. de mensajes en cola de mensajes: %ld\n", attr_rcv.mq_maxmsg);
      printf("Longitud max. de mensaje: %ld\n", attr_rcv.mq_msgsize);
      printf("Nros de mensajes pendientes en cola de mensajes: %ld\n", attr_rcv.mq_curmsgs);

      // Se lee de cola de mensajes
      leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
      if ((leido < 0))
      {
         printf("error en mq_receive()\n");
         exit(-1);
      }

      printf("Mensaje recibido: %s\n", buff);

      sleep(1);
   }

   exit(0);
}
