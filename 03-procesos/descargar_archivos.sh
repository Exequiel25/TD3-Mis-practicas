#!/bin/env sh

# Function to check if a file exists and download it if it does not
check_and_download() {
    local file_name=$1
    local url=$2

    if [ ! -f "$file_name" ]; then
        echo "Archivo $file_name no encontrado, descargando..."
        wget "$url"
    else
        echo "Archivo $file_name ya existe."
    fi
}