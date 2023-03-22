#!/bin/env sh

./prc12 2> err.txt	# todo mensaje de error será enviado al archivo "err.txt"
			# no será mostrado por pantalla
echo "El contenido del archivo 'err.txt' es:"
cat err.txt	# muestra el contenido de "err.txt"

# Observamos que la salida stdout es por pantalla,
# y stderr es lo que se guarda en el archivo
