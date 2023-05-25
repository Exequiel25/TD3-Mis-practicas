/*
 * Ejercicio 4 del TP Hilos
 *
 */
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int suma = 0;

void *hilo1(void *nro)
{
   int numero, temp;

   numero = *(int *)nro;
   temp = suma;
   // usleep(300);

   // pthread_yield(); // pthread_yield() is deprecated and should not be used
   // in new code. Instead, the standard function sched_yield()
   // should be used

   // sched_yield(); // el hilo cede el procesador
   temp = temp + 1;
   suma = temp;

   printf("Ejecutando hilo %d\n", numero);
   pthread_exit(NULL);
}

int main()
{
   pthread_t hilo[100];
   int rc, t, arre[100];

   // creamos 100 hilos
   for (t = 0; t < 100; t++)
   {
      printf("Creando el hilo %d\n", t);
      arre[t] = t;
      // todos ejecutan la misma funcion
      rc = pthread_create(&hilo[t], NULL, hilo1, (void *)(&arre[t]));
      if (rc)
      {
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);
      }
   }

   int i;
   for (i = 0; i < 100; i++)
   {
      // se esperan todos los hilos
      while (pthread_join(hilo[i], NULL))
         ;
   }

   printf("Valor de globlal = %d\n", suma);

   exit(0);
}
