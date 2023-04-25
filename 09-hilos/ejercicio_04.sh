#!/bin/env sh

gcc -o hilos04 hilos04.c -lpthread
./hilos04

# El programa suma una variable global compartida por todos los hilos.

# Cuando agregamos el usleep, el programa se comporta de manera diferente.
# Vemos que el resultado no es simpre 100, como debería, sino que es variable.
# Este se debe a la concurrencia de los hilos, que se ejecutan en paralelo.

# A veces el resultado es 100, pero otras veces es menor.
