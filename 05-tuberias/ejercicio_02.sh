#!/bin/env sh

gcc -o pipe_02 pipe_02.c
./pipe_02

# El problema que puede observarse en el programa,
# es que se intenta realizar una comunicación bidireccional.
# Es decir, el proceso padre escribe y lee,
# pero no podrá identificar si el que escribió en la tubería
# fue él o su proceso hijo

# Se podría utilizar patrones,
# n° fijos de bits,
# o agregar encabezados

