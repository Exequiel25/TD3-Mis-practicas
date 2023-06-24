#!/bin/env sh

gcc -o mutex01 mutex01.c -lpthread
./mutex01

# Los hilos comparten una variable que sumarán.
# Mutex debe evitar concurrencia
