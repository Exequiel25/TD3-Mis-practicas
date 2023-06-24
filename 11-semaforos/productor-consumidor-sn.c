// Problema productor-consumidor sincronizado con semáforos sin nombre.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define C 2
#define V 10

static int b[C] = {0};
pthread_t th1, th2;
sem_t sem_dato, sem_hueco;

void *productor(void *p)
{
    int i, dato;
    for (i = 0; i < V; i++)
    {
        dato = rand() % 100;
        sem_wait(&sem_hueco);
        b[i % C] = dato;
        printf("Productor: dato %d\n", dato);
        sem_post(&sem_dato);
    }
    pthread_exit(NULL);
}

void *consumidor(void *p)
{
    int i, dato;
    for (i = 0; i < V; i++)
    {
        sem_wait(&sem_dato);
        dato = b[i % C];
        printf("Consumidor: dato %d\n", dato);
        sem_post(&sem_hueco);
    }
    pthread_exit(NULL);
}

int main(void)
{
    sem_init(&sem_dato, 0, 0);
    sem_init(&sem_hueco, 0, C);
    pthread_create(&th1, NULL, productor, NULL);
    pthread_create(&th2, NULL, consumidor, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    sem_destroy(&sem_dato);
    sem_destroy(&sem_hueco);
    return 0;
}
