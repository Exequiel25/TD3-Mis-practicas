#!/bin/env sh
# Código en C

# Si los archivos no se encuentran en la carpeta, los descarga
. ../../descargar_archivos.sh
check_and_download "cliente.c" "https://github.com/td3-frm/practica/raw/refs/heads/master/27-sockets"
check_and_download "servidor.c" "https://github.com/td3-frm/practica/raw/refs/heads/master/27-sockets"

# Compila el código si no existe el ejecutable
if [ ! -f cliente ]; then
    gcc -o cliente cliente.c
fi
if [ ! -f servidor ]; then
    gcc -o servidor servidor.c
fi

echo "Ejecute servidor en una terminal y cliente en otra."