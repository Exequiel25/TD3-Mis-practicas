#!/bin/env sh
# Código en C

# Si los archivos no se encuentran en la carpeta, los descarga
if [ ! -f proc_03.c ]; then
    echo "Archivo proc_03.c no encontrado, descargando..."
    wget https://github.com/td3-frm/practica/raw/refs/heads/master/03-procesos/proc_03.c
fi

# Compila el código si no existe el ejecutable
if [ ! -f proc_03 ]; then
    gcc -o proc_03 proc_03.c
fi
echo "Ejecutando proc_03 (C)..."
echo "En otra terminal ejecute 'pstree -p | less' para buscar los procesos"
./proc_03

# Se observarán 4 procesos
# 1 padre de dos procesos,
# de los cuales una de esos hijos es padre de otro proceso
