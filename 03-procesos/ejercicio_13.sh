#!/bin/env sh

ls -al > ./stdout	# desvía el flujo de la respuesta ls -al, a un archivo "stdout"
			# no veremos nada por pantalla
cat stdout	# muestra el archivo por pantalla de stdout
