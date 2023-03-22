#!/bin/env sh

gcc -o prc10 prc10.c
./prc10

# El proceso del padre terminó por lo que el hijo queda huérfano.

# Podemos terminar el proceso con kill -9 PID
