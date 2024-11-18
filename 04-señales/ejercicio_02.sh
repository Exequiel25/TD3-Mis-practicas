#!/bin/env sh

gcc -o sig_02 sig_02.c
echo "Desde otra terminal ejecute kill -SIGKILL PID"

./sig_02

# Observamos que en la terminal donde se estaba ejecutando sig_02
# dejará de ejecutarse (terminó el proceso)
# y se mostrará un mensaje:
# "./ejercicio_02.sh: line 6: 37666 Killed                  ./sig_02"
# si fue ejecutado desde el script o
# "[1]    40074 killed     ./sig_02"
# si fue ejecutado desde ./sig_02

# Esto ocurre a pesar de haber especificado en el programa
# que ignoremos la señal KILL
