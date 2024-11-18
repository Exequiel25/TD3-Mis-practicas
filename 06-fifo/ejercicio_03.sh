#!/bin/env sh

gcc -o fifo_01 fifo_01.c
./fifo_01

# Abrimos la FIFO en modo escritura y lectura.

# Respecto a funcionamiento, es igual que el ejercicio 1.
# La diferencia es que ahora,
# veremos que los procesos no finalizan.