#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio4 ]; then
    gcc -o Ejercicio4 Ejercicio4.c -lm
fi

# Ejecutar el programa
./Ejercicio4