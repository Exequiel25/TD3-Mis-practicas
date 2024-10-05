#!/bin/env sh
# Código en Python

if [ ! -f proc_07.py ]; then
    echo "Archivo proc_07.py no encontrado, descargando..."
    wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_07.py
fi

echo "Ejecutando proc_07 (Python)..."
python3 proc_07.py

# En C utilizamos `fork()`
# En Python debemos utilizar la librería multiprocessing

# El proceso hijo debe ser iniciado con el método `start()`,
# que en C, no lo hacemos.

# También observamos que para acceder al id,
# debemos utilizar métodos(`getpid()`),
# y atributos (`pid`, `name`).

# Otra diferencia es que nosotros debemos finalizar
# el proceso hijo con el método `terminate()`

