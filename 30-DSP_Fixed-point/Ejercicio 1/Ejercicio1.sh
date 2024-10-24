#!/bin/env sh

# Ejecutar el código en C

# Compilar si no existe el ejecutable
if [ ! -f Ejercicio1 ]; then
    gcc -o Ejercicio1 Ejercicio1.c -lm
fi

# Ejecutar el programa
./Ejercicio1

echo "1. Verifique el valor de las variables c y d. ¿Son estos valores correctos?"
# Rta: No, en decimal c = a + b = 127 + 127 = 254, aunque su resultado fue -2,
# y d= a * b = 127 * 127 = 16129, aunque su resultado fue 1.
echo "2. De no ser así, ¿qué soluciones propone?"
# Rta: Cambiar el tipo de dato de las variables a y b a int16_t.
echo "3. Verifique el valor de las variables s1 y s2. ¿Son estos valores correctos?"
# s1 = -8 >> 2 => En binario (1 byte por ser char) 1111 1000 >> 2 = 1111 1110 = -2
# s2 = -1 >> 5 => En binario (1 byte por ser char) 1111 1111 >> 5 = 1111 1111 = -1