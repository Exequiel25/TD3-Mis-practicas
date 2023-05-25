/* Ejercicio 5 del TP de semaforos sin nombre */

/* productor-consumidor con semaforos */
/* similar a productor-consumidor con mutex */
/* agregamos un segundo hilo productor */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFFER 10		// Buffer
#define DATOS_A_PRODUCIR 20 // DATOS A PRODUCIR POR CADA PRODUCTOR

static int buffer[MAX_BUFFER] = {0}; // Buffer comun

pthread_t th1, th2, th3;			 // Hilos
sem_t sem_dato, sem_lugar, sem_prod; // Semaforos

//---------------- PRODUCTOR ---------------------------

void Productor(void)
{
	int dato, i, pos, s;

	pos = 0;
	dato = 1000; // Producir dato

	for (i = 0; i < DATOS_A_PRODUCIR / 2; i++)
	{ // cada productor produce la mitad de los datos
		// Para que no haya concurrencia
		s = sem_wait(&sem_prod);
		if (s == -1)
		{
			perror("sem_wait");
			exit(EXIT_FAILURE);
		}
		// Esperar que haya un lugar libre para producir
		s = sem_wait(&sem_lugar);
		if (s == -1)
		{
			perror("sem_wait");
			exit(EXIT_FAILURE);
		}

		// sleep(1);

		dato++;
		buffer[pos] = dato;
		pos = (pos + 1);

		if (pos >= MAX_BUFFER)
		{
			pos = 0;
		}

		// Y ya se puede producir otro dato
		s = sem_post(&sem_prod);
		if (s == -1)
		{
			perror("sem_post");
			exit(EXIT_FAILURE);
		}
		// Indicar que hay un dato mas
		s = sem_post(&sem_dato);
		if (s == -1)
		{
			perror("sem_post");
			exit(EXIT_FAILURE);
		}

		printf("Productor dato: %d \n", dato);
	}

	printf("Termina Productor: %d\n", i);
	pthread_exit(0);
}

//---------------- CONSUMIDOR ---------------------------
void Consumidor(void)
{
	int dato, i, pos, s;

	pos = 0;

	for (i = 0; i < DATOS_A_PRODUCIR; i++)
	{
		sleep(1);

		// Esperar que haya un dato antes de consumir
		s = sem_wait(&sem_dato);
		if (s == -1)
		{
			perror("sem_wait");
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < MAX_BUFFER; j++)
		{
			// si hay dato
			if (buffer[j] != 0)
			{
				dato = buffer[j];
				buffer[j] = 0;
				break;
			}
		}

		// dato = buffer[pos];
		// pos = (pos + 1);
		// if (pos >= MAX_BUFFER)
		// {
		// 	pos = 0;
		// }

		// Indicar que hay un lugar libre mas
		s = sem_post(&sem_lugar);
		if (s == -1)
		{
			perror("sem_post");
			exit(EXIT_FAILURE);
		}

		printf("Consumidor dato: %d \n", dato);
	}

	printf("Termina Consumidor: %d\n", i);
	pthread_exit(0);
}

//-------------------------------------------------------

int main()
{

	int s;

	printf("Se crean semaforos\n");

	//------ Crear semaforos
	s = sem_init(&sem_dato, 0, 0); // semaforo inicializado en 0
	if (s == -1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	s = sem_init(&sem_lugar, 0, MAX_BUFFER); // semaforo inicializado en MAX_BUFFER
	if (s == -1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	s = sem_init(&sem_prod, 0, 1); // semaforo inicializado en 1
	if (s == -1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	//------ Crear hilos

	printf("Se crean hilos\n");

	pthread_create(&th1, NULL, (void *)&Productor, NULL);
	pthread_create(&th2, NULL, (void *)&Consumidor, NULL);
	pthread_create(&th3, NULL, (void *)&Productor, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);

	//------ Destruir semaforos
	s = sem_destroy(&sem_dato);
	if (s == -1)
	{
		perror("sem_destroy");
		exit(EXIT_FAILURE);
	}
	s = sem_destroy(&sem_lugar);
	if (s == -1)
	{
		perror("sem_destroy");
		exit(EXIT_FAILURE);
	}

	printf("Termina main() \n");

	pthread_exit(0);
}

//------------------------------------------------------------//
