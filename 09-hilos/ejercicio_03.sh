#!/bin/env sh

gcc -o hilos03 hilos03.c -lpthread
./hilos03

# El objetivo es crear 2 hilos que sigan rutinas diferentes,
# donde el hilo 1 espera a que el hilo 0 termine.
# Finalmente, el hilo main espera a que el hilo 1 termine.

# Al descomentar el pthread_detach() del hilo 0,
# los recursos son automaticamente liberados al terminar el hilo,
# sin necesidad de esperar a que el hilo termine con join.

# Al descomentar pthread_exit(),
# y reemplazarlo por exit(0), 
# el proceso no espera los 2 segundos del hilo 0,
# y termina inmediatamente. (main no espera a los hilos)
