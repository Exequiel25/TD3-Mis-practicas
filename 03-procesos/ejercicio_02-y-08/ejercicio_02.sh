#!/bin/env sh
# Código en C

# Si los archivos no se encuentran en la carpeta, los descarga
if [ ! -f proc_02.c ]; then
    echo "Archivo proc_02.c no encontrado, descargando..."
    wget https://github.com/td3-frm/practica/raw/refs/heads/master/03-procesos/proc_02.c
fi

# Compila el código si no existe el ejecutable
if [ ! -f proc_02 ]; then
    gcc -o proc_02 proc_02.c
fi
echo "Ejecutando proc_02 (C)..."
./proc_02


# Se observarán ambos procesos en ejecución

# Observamos que al finalizar el procesos del padre,
# en la tabla de procesos existe un proceso huérfano,
# el cual corresponde al proceso hijo que no ha terminado
# El proceso hijo es adoptado por un proceso superior,
# generalmente systemd
