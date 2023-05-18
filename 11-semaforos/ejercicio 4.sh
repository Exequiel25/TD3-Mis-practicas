#!/bin/env sh

gcc -o sem04 sem04.c
./sem04

# Se utilizan 2 semáforos, uno inicia en 0 y otro en el tamaño del Buffer.
# De esta forma, si el consumidor es más rápido que el productor,
# o viceversa, no habrá problemas.