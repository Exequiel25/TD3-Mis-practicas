#!/bin/env sh

gcc -o prc11 prc11.c
./prc11

# El proceso del hijo terminó, pero no el del padre.
# Por lo tanto el hijo pasa a ser un proceso "zombie"

# Podemos terminar el proceso con Ctrl + C para interrumpirlo.
