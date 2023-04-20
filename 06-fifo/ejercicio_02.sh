#!/bin/env sh

gcc -o fifo_01 fifo_01.c
./fifo_01

# Para que sea no bloqueante,
# debemos abrir con O_NONBLOCK.

# Lo que observamos,
# es que ninguna de los dos procesos
# espera a que haya algún contenido en la FIFO.
# Por lo que entienden que no hay nada que leer.
# Y terminan.