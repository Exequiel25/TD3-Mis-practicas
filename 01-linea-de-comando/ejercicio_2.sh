#!/usr/bin/env sh
mkdir ~/ejercicio_bash_avanzado	# Crea una carpeta en el directorio home con el nombre ejercicio_bash_avanzado
cd ~/ejercicio_bash_avanzado	# Cambia el directorio a ~/ejercicio_bash_avanzado
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/hola.zip		# Descarga el archivo zip hola.zip del repositorio de github
unzip hola.zip		# Descomprime el archivo zip
mv hola.c hola-mundo.c	# Renombra el archivo hola.c a hola-mundo.c
gcc hola-mundo.c -o hola-mundo	# Compila el archivo hola-mundo.c
ls			# Verifica la creación de archivo ejecutable
./hola-mundo		# Ejecuta el archivo ejecutable
			# Se debe anteponer un "./" para indicar la ruta del archivo, el '.' indica el directorio actual
			# Es equivalente a la ruta absoluta "~/ejercicio_bash_avanzado/hola-mundo"
