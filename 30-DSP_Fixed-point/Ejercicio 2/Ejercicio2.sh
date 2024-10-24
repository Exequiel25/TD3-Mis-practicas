#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio2 ]; then
    gcc -o Ejercicio2 Ejercicio2.c -lm
fi

# Ejecutar el programa
./Ejercicio2 2.4515