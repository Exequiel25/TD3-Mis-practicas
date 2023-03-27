#!/bin/env sh

gcc -o prc16 prc16.c
./prc16

# Al ejecutar exec(), se intenta hacer un ls a la ruta:
# /otro_directorio/ls
# La cual, como no existe (en mi caso), retorna un error
