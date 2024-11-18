#!/bin/env sh

gcc -o mq02 mq02.c -lrt
./mq02

# El objetivo del código es enviar mensajes a una cola de mensajes.
# El problema es que no hay nadie para recibirlos.
# Por lo que, cuando se llegue al límite de mensajes, el programa se bloqueará.