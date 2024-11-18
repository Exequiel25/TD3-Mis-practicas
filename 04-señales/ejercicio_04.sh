#!/bin/env sh

gcc -o sig_03 sig_03.c
echo "Desde otra terminal ejecute kill -SIGKILL PID"

./sig_03

# Observamos que en la terminal donde se estaba ejecutando sig_03
# dejará de ejecutarse (terminó el proceso)
# Esto ocurre a pesar de haber especificado un manejador
# Es decir, SIGKILL actúa por default
