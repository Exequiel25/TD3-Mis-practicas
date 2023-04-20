#!/bin/env sh

gcc -o fifo_01 fifo_01.c
./fifo_01

echo -e "\n***Verifica que se haya creado la FIFO***\n"
ls /tmp

# Si descomentamos las últimas,
# al ejecutar ls /tmp,
# no veremos el archivo.