#!/bin/env sh

gcc -o hilos02 hilos02.c -lpthread
./hilos02

# Deberíamos ver la creación de 5 hilos,
# cada uno de los cuales imprime un mensaje
# y termina.

# El último printf() es el de la función main(),
# pero está luego de pthread_exit(),
# por lo que no se ejecuta.

# Si hacemos el cambio, veremos que todos los hilos son 5,
# esto ocurre porque la variable que indica el numero del hilo,
# es global, por lo que todos los hilos la comparten.
# (cuando creamos el hilo compartimos esa memoria).

# Vemos el valor 5 porque se ejecuta primero el hilo main.
