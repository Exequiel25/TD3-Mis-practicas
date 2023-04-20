#!/bin/env sh

gcc -o mq02 mq02.c -lrt
gcc -o mq03 mq03.c -lrt

# RECORDAR TERMINAR LOS PROCESOS CON SIGUSR1

# Si se ejecutan en la misma instancia,
# veremos que si ejecutamos primero el de lectura,
# termina con error.
# Si ejecutamos primero el de escritura,
# escribe los mensajes y cuando llega al último posible,
# termina en error.
# Luego podemos ejecutar el de lectura,
# que lee los mensajes y termina en error.

# Si se ejecutan al mismo tiempo,
# se produce un bucle infinito