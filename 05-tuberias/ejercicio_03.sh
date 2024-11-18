#!/bin/env sh

gcc -o pipe_03 pipe_03.c
./pipe_03

# El problema que se presenta, si observamos,
# es que se imprime ambas FRASES,
# y el segundo mensaje es de error, ya que se vacía la tubería.

# Una posible solución, es añadir un identificador en el mensaje,
# como un salto de línea.
# Otra opción, sería realizar la lectura del primer hijo creado
# antes de crear al segundo

