/*
Un proceso posee 3 hilos (main, hilo0, hilo1). Los hilos (main, hilo0, hilo1)  incrementan las variables total y total1.  Para sincronizar las sumas el hilo1 debe esperar al hilo0 antes de acceder a las variables (total y total1), y el hilo main debe esperar al hilo1 antes de acceder a las variables (total y total1). Completar
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t h[2];
int total, total1;

void *hilo0(void *arg)
{
    int t;
    for (t = 0; t < 100000; t++)
    {
        total = total + 1;
        total1 = total1 + 1;
    }
    pthread_exit(NULL);
}

void *hilo1(void *arg)
{
    int t;
    pthread_join(h[0], NULL);
    for (t = 0; t < 10000; t++)
    {
        total++;
        total1++;
    }
    pthread_exit(NULL);
}

int main()
{
    int t;
    total = 20000;
    total1 = 0;
    pthread_create(&h[0], NULL, hilo0, NULL);
    pthread_create(&h[1], NULL, hilo1, NULL);
    pthread_join(h[1], NULL);
    for (t = 0; t < 1000000; t++)
    {
        total = total + 1;
        total1 = total1 + 1;
    }
    printf("Total= %d, Total1= %d\n", total, total1);
    pthread_exit(NULL);

    return 0;
}
