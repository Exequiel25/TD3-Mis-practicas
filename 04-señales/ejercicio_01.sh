#!/bin/env sh

gcc -o sig_01 sig_01.c
./sig_01

echo $?
echo "Estado de salida (exit status)"

# Si termina en forma normal, el exit status es 5
# debido a que escribimos en el código sig_01.c
# un exit(5)

# Cuando interrumpimos el proceso con Ctrl+C,
# exit status indica un valor de 130 indicando
# que el proceso termino de forma abrupta
