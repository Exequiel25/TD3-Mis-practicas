#!/bin/env sh

gcc -o prc03 prc03.c
echo "En otra terminal ejecute 'pstree -p | less' para buscar los procesos"
./prc03

# Se observarán 4 procesos
# 1 padre de dos procesos,
# de los cuales una de esos hijos es padre de otro proceso
