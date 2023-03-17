#!/usr/bin/env sh
mkdir ~/ejercicio_rutas	# Crea una carpeta en el directorio home con el nombre ejercicio_rutas
cd ~/ejercicio_rutas	# Cambia el directorio a ~/ejercicio_rutas
mkdir fotos videos documentos	# Crea 3 subcarpetas
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/Paul-Cezanne_Still-Life-With-Apples.jpeg	# Descarga archivo de imagen
mv Paul-Cezanne_Still-Life-With-Apples.jpeg fotos/	# Mueve la imagen a la subcarpeta fotos
echo > 1342-0.txt	# Crea archivo de texto 1342-0.txt
mv 1342-0.txt documentos/	# Mueve el archivo de texto a subcarpeta documentos
mkdir $(pwd)/backup	# Crea una subcarpeta "backup" con argumento ruta absoluta de pwd
cp $(pwd)/documentos/1342-0.txt $(pwd)/backup	# Copia el archivo de texto a la subcarpeta "backup"
