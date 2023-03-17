#!/usr/bin/env sh
mkdir ~/ejercicio_bash	# Crea una carpeta en el directorio home con el nombre ejercicio_bash
cd ~/ejercicio_bash	# Cambia el directorio a ~/ejercicio_bash
touch ejercicio.txt	# Crea un archivo vacío ejercicio.txt
ls			# Lista el directorio actual
echo "Hola, mundo!" > ejercicio.txt	# Escribe la frase "Hola, mundo!" en el archivo ejercicio.txt
cat ejercicio.txt	# Muestra el contenido de ejercicio.txt
mkdir subcarpeta	# Crea una carpeta "subcarpeta"
cp ejercicio.txt subcarpeta/	# Copia el archivo ejercicio.txt dentro de la subcarpeta
ls subcarpeta		# Muestra el contenido de "subcarpeta"
