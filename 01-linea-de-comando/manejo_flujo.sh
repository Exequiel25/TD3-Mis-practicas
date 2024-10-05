#!/usr/bin/env sh

# Compilar el programa en c
gcc manejo_flujo.c -o output
# Ejecutar el programa en c (normal)
echo "Ejecutando el programa en c..."
./output
# Ejecutar el programa en c pero redirigiendo la salida al archivo stdout
echo "Ejecutando el programa en c con salida redirigida a stdout.txt..."
./output 1> stdout.txt
# Ejecutar el programa en c pero redirigiendo la salida de error al archivo error.txt
echo "Ejecutando el programa en c con salida de error redirigida a error.txt..."
./output 2> error.txt