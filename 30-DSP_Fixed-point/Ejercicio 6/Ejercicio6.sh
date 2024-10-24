#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio6 ]; then
    gcc -o Ejercicio6 Ejercicio6.c -lm
fi

# Ejecutar el programa
./Ejercicio6