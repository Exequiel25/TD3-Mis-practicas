#!/bin/env sh

ls / | head -3 | tail -1 > myoutput
cat myoutput

# head imprime las primeras 3 lineas de la salida de ls /
# tail imprime la última linea
# el contenido de myoutput es 'dev'
# >> agrega sin borrar (append)
# > sobreescribe en el archivo (no agrega al contenido)

