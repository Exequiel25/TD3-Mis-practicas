#!/bin/env sh
# Código en Python

if [ ! -f proc_08.py ]; then
    echo "Archivo proc_08.py no encontrado, descargando..."
    wget https://github.com/td3-frm/practica/raw/refs/heads/master/03-procesos/proc_08.py
fi

echo "Ejecutando proc_08 (Python)..."
python3 proc_08.py

# La variable 'suma' pasa a ser un objeto
# al que puede acceder más de un proceso
