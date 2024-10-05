#!/bin/env sh
# Código en C

# Si los archivos no se encuentran en la carpeta, los descarga
. ../descargar_archivos.sh
check_and_download "proc_01.c" "https://github.com/td3-frm/practica/raw/master/03-procesos/proc_01.c"

# Compila el código si no existe el ejecutable
if [ ! -f proc_01 ]; then
    gcc -o proc_01 proc_01.c
fi
echo "Ejecutando proc_01 (C)..."
./proc_01

# El PID es la identificación del proceso (Process ID)
# El PPID (Parent Process ID) es siempre menor que la del hijo

# Con ayuda de pstree podemos ver que:
# El padre crea 3 hijos (uno por bucle),
# de los cuales 1 hijo no es padre (el tercer hijo creado),
# 1 hijo es padre de 1 único proceso (el segundo hijo creado),
# y el otro hijo es padre de 2 hijos (el primer hijo creado).

# De estos últimos, 1 hijo es padre de otro proceso,
# y el otro no tiene hijo

# Con la variable de control y comparando los PID,
# podemos ver cómo cada hijo al momento de ser creado tiene
# un valor de control diferente,
# que es igual a la variable de control del padre
# al momento de hacer 'fork()'
