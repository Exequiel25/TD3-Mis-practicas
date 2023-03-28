#!/bin/env sh

gcc -o sig_05 sig_05.c
./sig_05

# Un problema evidente es,
# si el proceso hijo termina antes de definir
# el manejador de señales,
# el padre no podrá leer el estado de finalización.
# Y además el proceso hijo quedará en estado zombie
# hasta la finalización del proceso padre.

# Por el contrario, si definimos primero el manejador de señales,
# cuando el proceso hijo termina, el padre recibe la señal, 
# realiza la rutina del manejador, y termina el proceso padre.
# Como el padre atiende a la señal de terminación del proceso hijo,
# este no termina en un estado zombie
