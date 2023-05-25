/*
 * Ejercicio 1 del TP Hilos
 *
 */

#include <pthread.h> // libreria necesaria para trabajar con hilos
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *hola(void *nro)
{
   // start routine de los hilos
   sleep(2);
   printf("Hola, soy el hilo %d\n", *(int *)nro);
   // termina el hilo
   pthread_exit(NULL);
   // exit(0);
}

int main()
{

   pthread_t hilo[1];
   int rc, t;

   t = 0;

   printf("Main creando el hilo nro %d\n", t);

   // crea un hilo
   rc = pthread_create(&hilo[0], /*attr*/ NULL, /*start routine*/ hola, /*arg*/ (void *)(&t));

   if (rc != 0)
   {
      // si rc es distinto de 0 hubo error
      printf("ERROR; pthread_create() = %d\n", rc);
      exit(-1);
   };

   printf("Espera a que termine hilo\n");

   pthread_join(hilo[0], NULL);

   printf("Termina hilo main\n");

   pthread_exit(NULL);

   return 0;
}
