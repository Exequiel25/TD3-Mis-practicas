/*
 * PARCIAL 2: programa para ser ejecutado por el proceso padre.
 *
 * Comando para compilar:
 *
 * gcc -Wall -c hijo.c -lrt && gcc -Wall -c padre.c -lrt && gcc -Wall hijo.o padre.o -o padre -lrt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>

int hijo(mqd_t mqd);

#define MQ_PATH "/MQ_TD3" // El nombre de la cola de mensajes debe empezar con "/"

int main(void)
{
	int pid;
	int err, leido;
	char buff[1024];
	mqd_t mqd;
	struct mq_attr attr;
	struct mq_attr attr_rcv;

	// Se elimina cola de mensajes
	err = mq_unlink(MQ_PATH);
	if (err == -1)
	{
		printf("Padre: error en mq_unlink (%d).\n", err);
		//~ exit(-1);
	}
	else
	{
		printf("Padre: Cola de mensajes eliminada (%d)\n", err);
	}

	// Se fijan algunos parametros de la cola de mensajes antes de crearla
	attr.mq_msgsize = sizeof(buff);
	attr.mq_maxmsg = 3;

	// Se abre o crea cola de mensajes
	// **** RESOLUCION DEL EJERCICIO *******************************
	mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0666, &attr);
	// *************************************************************
	if (mqd < 0)
	{
		printf("Padre: error en mq_open (%d).\n", mqd);
		exit(-1);
	}
	else
	{
		printf("Padre: cola de mensajes creada.\n");
	}

	if ((pid = fork()) == -1)
	{
		perror("Padre: erorr en fork.\n");
		return -1;
	}

	// codigo que ejecuta el hijo
	if (0 == pid)
	{
		hijo(mqd);
		return 0;
	}
	// codigo que ejecuta el padre
	else
	{
		printf("Padre en ejecucion... \n");

		sleep(1);

		// **** RESOLUCION DEL EJERCICIO *******************************

		// Leemos el mensaje de la cola de mensajes
		leido = mq_receive(mqd, buff, sizeof(buff), NULL);
		if (leido < 0)
		{
			printf("Padre: error en mq_receive (%d).\n", leido);
			exit(-1);
		}
		else
		{
			printf("Padre: mensaje recibido.\n");
		}

		// Imprimimos el mensaje recibido
		printf("Padre: mensaje recibido: %s\n", buff);

		// Cerramos la cola de mensajes
		err = mq_close(mqd);
		if (err < 0)
		{
			printf("Padre: error en mq_close (%d).\n", err);
			exit(-1);
		}
		else
		{
			printf("Padre: cola de mensajes cerrada.\n");
		}

		// Eliminamos la cola de mensajes
		err = mq_unlink(MQ_PATH);
		if (err < 0)
		{
			printf("Padre: error en mq_unlink (%d).\n", err);
			exit(-1);
		}
		else
		{
			printf("Padre: cola de mensajes eliminada.\n");
		}

		// *************************************************************

		wait(NULL);

		return 0;
	}
}
