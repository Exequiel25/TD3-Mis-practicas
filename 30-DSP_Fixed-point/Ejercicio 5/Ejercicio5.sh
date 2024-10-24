#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio5 ]; then
    gcc -o Ejercicio5 Ejercicio5.c -lm
fi

# Ejecutar el programa
./Ejercicio5