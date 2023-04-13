#!/bin/env sh

gcc -o pipe_01 pipe_01.c
./pipe_01

# Declaramos un arreglo entero fd[2] para luego
# inicializar los descriptores con la llamada pipe(fd).
# Así tenemos entonces, los descriptores de lectura y escritura
# definidos.
# Luego creamos el proceso hijo,
# el cual también tiene los mismos descriptores.
# En uno cerramos el descriptor escritura y en el otro el de lectura
# O viceversa

