#!/bin/env sh

python proc_01.py

# En C utilizamos `fork()`
# En Python debemos utilizar la librería multiprocessing

# El proceso hijo debe ser iniciado con el método `start()`,
# que en C, no lo hacemos.

# También observamos que para acceder al id,
# debemos utilizar métodos(`getpid()`),
# y atributos (`pid`, `name`).

# Otra diferencia es que nosotros debemos finalizar
# el proceso hijo con el método `terminate()`
