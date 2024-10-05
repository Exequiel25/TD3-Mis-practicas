#!/bin/env bash
# Usando bash para poder usar arrays
# Código en Python

# Array of required files
files=("p09a.py" "p09b.py" "p09c.py" "p09d.py")

# Base URL for downloading files
base_url="https://github.com/td3-frm/practica/raw/refs/heads/master/03-procesos/"

# Check and download missing files
for file in "${files[@]}"; do
    if [ ! -f "$file" ]; then
        echo "Archivo $file no encontrado, descargando..."
        wget "${base_url}${file}"
    fi
done

# Execute each Python file
for file in "${files[@]}"; do
    echo "Ejecutando $file (Python)..."
    python3 "$file"
done

# Vemos que el proceso padre espera a que el hijo termine.
