#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio3 ]; then
    gcc -o Ejercicio3 Ejercicio3.c -lm
fi

# Ejecutar el programa
./Ejercicio3 2.4515 3.1415