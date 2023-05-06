#!/bin/env sh

gcc -o pipe_01 pipe_01.c
./pipe_01

# Declaramos un arreglo entero fd[2] para luego
# inicializar los descriptores con la llamada pipe(fd).
# Así tenemos entonces, los descriptores de lectura y escritura
# definidos.
# Luego creamos el proceso hijo,
# el cual también tiene los mismos descriptores.
# En uno cerramos el descriptor escritura y en el otro el de lectura
# O viceversa

# InterProcess Communication (IPC)
# Comunicación entre procesos

# Pipes
# Un pipe es un mecanismo de IPC que permite la comunicación de datos entre procesos relacionados.
# Persisten mientras exista el proceso que los creó.
# Es una tubería sin nombre, unidireccional, que permite la comunicación entre procesos.
# Buffer circular de tamaño fijo en memoria del kernel.

# Conexión entre salida estándar de un proceso y entrada estándar de otro proceso.
# Se utilizan descriptor de archivos para acceder a ellos:
# 0. Entrada estándar (stdin).
# 1. Salida estándar (stdout).
# 2. Salida de error estándar (stderr).

# Al crear un pipe, se crean dos descriptores de archivos:
# 1. fd[0]: Descriptor de lectura.
# 2. fd[1]: Descriptor de escritura.
# Luego se debe crear un proceso hijo, el cual hereda los descriptores de archivos del padre.
# El padre cierra el descriptor de escritura y el hijo cierra el descriptor de lectura (o viceversa).
# Si se cierran todos los descriptores de lectura, el kernel envía una señal SIGPIPE al proceso que intenta escribir en el pipe.
# Si se cierran todos los descriptores de escritura, el kernel envía un EOF al proceso que intenta leer del pipe.
# Si se cierran todos los descriptores de lectura y escritura, el kernel libera el buffer del pipe (se destruye).

# Situaciones de conflicto:
# 1. Un proceso lee una tubería vacía se bloquea.
# 2. Un proceso escribe en una tubería llena se bloquea.
# 3. Si dos procesos quieren leer desde la misma tubería, el primero que lo haga obtiene los datos, pero no sabemos cuál fue el primero.
# 4. Cuando el proceso intenta escribir en una tubería con descriptores de lectura cerrados, el kernel envía una señal SIGPIPE al proceso y lo termina.

# En bash, el operador | crea un pipe entre dos procesos (pipeline).