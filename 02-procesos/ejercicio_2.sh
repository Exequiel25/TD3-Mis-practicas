#!/bin/env sh

gcc -o prc02 prc02.c
echo "En otra terminal ejecute 'pstree -p | less' para buscar los procesos"
./prc02

# Se observarán ambos procesos en ejecución
