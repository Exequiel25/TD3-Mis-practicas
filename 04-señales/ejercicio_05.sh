#!/bin/env sh

gcc -o sig_03 sig_03.c
echo "Desde otra terminal ejecute kill -SIGKILL PID"

./sig_03

# Para este caso, si vemos que el manejador está funcionando
# e imprime en pantalla "Me rehuso a terminar\n"
