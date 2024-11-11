#!/bin/env sh
# Código en C

# Si los archivos no se encuentran en la carpeta, los descarga
. ../../descargar_archivos.sh
check_and_download "clienteu.c" "https://github.com/td3-frm/practica/raw/refs/heads/master/27-sockets"
check_and_download "servidoru.c" "https://github.com/td3-frm/practica/raw/refs/heads/master/27-sockets"

# Compila el código si no existe el ejecutable
if [ ! -f clienteu ]; then
    gcc -o clienteu clienteu.c
fi
if [ ! -f servidoru ]; then
    gcc -o servidoru servidoru.c
fi

echo "Ejecute servidoru en una terminal y clienteu en otra."