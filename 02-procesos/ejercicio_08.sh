#!/bin/env sh

gcc -o prc08 prc08.c
./prc08

# Observamos que al finalizar el procesos del padre,
# en la tabla de procesos existe un proceso huérfano,
# el cual corresponde al proceso hijo que no ha terminado
# El proceso hijo es adoptado por un proceso superior,
# generalmente systemd
