/*
 * Ejercicio 5 del TP de Cola de mensajes
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
mqd_t mqd = 0;
struct mq_attr attr, attr_rcv;
struct sigevent sev;
int retval;

void lee_mensaje(int a)
{

   write(STDOUT_FILENO, "\nleer mensaje\n", sizeof("\nleer mensaje\n"));

   //-- lee en cola de mensajes --------------------------
   leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, NULL);
   if (leido == -1)
   {
      write(STDOUT_FILENO, "\nerror en mq_receive()\n", sizeof("\nerror en mq_receive()\n"));
   }
   else
   {
      write(STDOUT_FILENO, "\nMensaje recibido: ", sizeof("\nMensaje recibido: "));
      write(STDOUT_FILENO, buff, leido);
      write(STDOUT_FILENO, "\n", sizeof("\n"));
   }
}

void finaliza_proceso(int a)
{

   // cerramos la cola de mensajes
   err = mq_close(mqd);
   if ((err < 0))
   {
      write(STDOUT_FILENO, "\nerror en mq_close()\n", sizeof("\nerror en mq_close()\n"));
      exit(0);
   }

   write(STDOUT_FILENO, "\nCola de mensajes cerrada\n", sizeof("\nCola de mensajes cerrada\n"));

   // elimina la cola de mensajes
   err = mq_unlink(MQ_PATH);
   if (err == -1)
   {
      write(STDOUT_FILENO, "\nerror en mq_unlink()\n", sizeof("\nerror en mq_unlink()\n"));
      exit(0);
   }

   write(STDOUT_FILENO, "\nCola de mensajes eliminada\n", sizeof("\nCola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "\nTerminando proceso...\n", sizeof("\nTerminando proceso...\n"));

   exit(0);
}

int main()
{

   // Manejadores
   signal(SIGINT, lee_mensaje);       // Ctrl + C
   signal(SIGUSR1, finaliza_proceso); // termina

   // muestra el PID del proceso
   printf("Soy el proceso: %d \n ", getpid());

   // abrir y crear cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDONLY);
   if (mqd < 0)
   {
      printf("error en mq_open()");
      exit(-1);
   }

   printf("Cola de mensajes abierta\n");

   // obtiene los parámetros de la cola de mensjaes
   if (mq_getattr(mqd, &attr_rcv) == -1)
   {
      printf("error en mq_getattr()");
      exit(-1);
   }
   printf("Nro max. de mensajes en cola de mensajes: %ld\n", attr_rcv.mq_maxmsg);
   printf("Longitud max. de mensaje: %ld\n", attr_rcv.mq_msgsize);
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n", attr_rcv.mq_curmsgs);

   while (1)
   {
      // no hago nada
      // solo soy útil cuando recibo una señal

   } // fin while

   exit(0);
}
