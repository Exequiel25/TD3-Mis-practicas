#!/bin/env sh

gcc -o prc05 prc05.c
./prc05
# A pesar de que el padre decrementa en 1 a x,
# y el hijo incremente en 1 a x,
# dichas variables a pesar de tener nombres iguales son diferentes.

# Esto es porque el proceso hijo copió las variables del padre en el momento
# de ser creador, cuando x = 100.
