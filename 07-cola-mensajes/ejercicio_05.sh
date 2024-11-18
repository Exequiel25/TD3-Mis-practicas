#!/bin/env sh

gcc -o mq05 mq05.c -lrt
gcc -o mq05a mq05a.c -lrt
./mq05

# RECORDAR TERMINAR LOS PROCESOS CON SIGUSR1