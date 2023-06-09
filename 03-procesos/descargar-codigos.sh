#!/usr/bin/env sh
#wget https://github.com/td3-frm/practica/raw/master/02-procesos/procesos_c.zip
#unzip procesos_c.zip
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_01.c
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_01.py
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_02.c
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_02.py
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_03.c
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_05.c
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_09.c
wget https://github.com/td3-frm/practica/raw/master/03-procesos/proc_15.c

# Un proceso es la abstracción de un programa en ejecución, que tiene asociado
# los registros utilizados, el contador de programa, la pila, el conjunto de
# descriptores de archivos abiertos, variables, etc.

# Estados de un proceso
# 1. Nuevo: El proceso está siendo creado.
# 2. Listo: El proceso está listo para ser ejecutado.
# 3. En ejecución: El proceso está siendo ejecutado.
# 4. Bloqueado: El proceso está esperando por un evento.
# 5. Terminado: El proceso ha terminado su ejecución.

# Creación de procesos
# 1. Fork: Se crea un proceso hijo a partir de un proceso padre (llamada a sistema).
# 2. Inicialización del sistema.
# 3. Petición del usuario para crear un proceso.
# 4. Inicio de trabajo en batch.
# (batch es un programa que se ejecuta en un sistema informático sin la interacción del usuario)

# Terminación de procesos
# 1. Terminación normal: El proceso termina su ejecución (voluntaria).
# 2. Terminación por error: El proceso termina su ejecución por un error (voluntaria).
# 3. Terminación por otro proceso: El proceso termina su ejecución por otro proceso (involuntaria).
# 4. Terminación por el sistema operativo: El proceso termina su ejecución por el sistema operativo, quien detecta un error fatal (involuntaria).

# Memoria de un proceso
# 1. Código (segmento text): Código del programa.
# 2. Datos: Variables globales y estáticas.
# 2.a. Datos inicializados.
# 2.b. Datos no inicializados.
# 3. Pila: contiene un macro de datos por cada llamada a función (variación dinámica).
# 4. Montón: Memoria dinámica, variables creadas en tiempo de ejecución (variación dinámica).

# Llamadas a sistema
# 1. Creación de procesos: fork,
# 2. Cambiar código de un proceso: exec, execv, execl, execlp, execle,
# 3. Terminación de procesos: exit,
# 4. Espera de un proceso: wait,
# 5. Obtener identificador de proceso: getpid,
# 6. Obtener identificador de proceso padre: getppid,
