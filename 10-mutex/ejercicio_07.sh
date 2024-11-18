#!/bin/env sh

gcc -o mutex06 mutex06.c -lpthread
./mutex06

# El programa crea 2 hilos, uno consume y el otro produce
# (es decir, uno ingresa un valor a un array, 
# y el otro quita ese valor)
#
# En la analogia, el buffer viene a ser el stock,
# y el dato el producto.
