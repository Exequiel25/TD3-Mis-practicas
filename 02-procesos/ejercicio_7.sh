#!/bin/env sh

gcc -o prc07 prc07.c
./prc07

# Con ayuda de pstree podemos ver que:
# El padre crea 3 hijos (uno por bucle),
# de los cuales 1 hijo no es padre (el tercer hijo creado),
# 1 hijo es padre de 1 único proceso (el segundo hijo creado),
# y el otro hijo es padre de 2 hijos (el primer hijo creado).

# De estos últimos, 1 hijo es padre de otro proceso,
# y el otro no tiene hijo

# Con la variable de control y comparando los PID,
# podemos ver cómo cada hijo al momento de ser creado tiene
# un valor de control diferente,
# que es igual a la variable de control del padre
# al momento de hacer 'fork()'
