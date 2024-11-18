#!/bin/env sh

gcc -o pipe_04 pipe_04.c
./pipe_04

# El problema evidente es que antes de crear el proceso hijo,
# estamos cerrando el descriptor de lectura.
# Por eso termina en error ejecutando 'echo $'

