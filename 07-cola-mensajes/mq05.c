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

void escribe_mensaje(int a)
{

   write(STDOUT_FILENO, "\nenviar mensaje\n", sizeof("\nenviar mensaje\n"));

   //-- Escribe en cola de mensajes --------------------------
   err = mq_send(mqd, MENSAJE, strlen(MENSAJE) + 1, 1); // strlen nos da la longitud de una cadena
   if (err == -1)
   {
      write(STDOUT_FILENO, "\nerror en mq_send()\n", sizeof("\nerror en mq_send()\n"));
   }
   else
   {
      write(STDOUT_FILENO, "\nMensaje enviado\n", sizeof("\nMensaje enviado\n"));
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
   signal(SIGINT, escribe_mensaje);   // Ctrl + C
   signal(SIGUSR1, finaliza_proceso); // termina

   // muestra el PID del proceso
   printf("Soy el proceso: %d \n ", getpid());

   // elimina en el caso que exista, la cola de mensajes
   mq_unlink(MQ_PATH);

   // establece parámetros de la cola de mensajes
   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;

   // abrir y crear cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0666, &attr);
   if (mqd < 0)
   {
      printf("error en mq_open()");
      exit(-1);
   }

   printf("Cola de mensajes creada\n");

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
