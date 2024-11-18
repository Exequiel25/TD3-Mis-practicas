#!/bin/env sh

gcc -o fifo_01 fifo_01.c
./fifo_01

echo -e "\n***Verifica que se haya creado la FIFO***\n"
ls /tmp

# Si descomentamos las últimas,
# al ejecutar ls /tmp,
# no veremos el archivo.

# Similar a una tubería, con la diferencia que se crea en el sistema de archivos.
# FIFO: First In First Out.
# Se crea con la llamada mkfifo.
# Se abre con la llamada open, al igual que un archivo.
# Pueden ser bloqueantes o no bloqueantes.
# Los procesos no relacionados pueden comunicarse a través de una FIFO.
# Una vez que se crea una FIFO cualquiera puede escribir en ella y leer de ella.
# Aunque todos los descriptores de archivos de escritura se cierren, los datos permanecen en la FIFO hasta que todos los descriptores de archivos de lectura se cierren.
# Si se cierran los descriptor de archivos de lectura, los procesos que intenten leer de la FIFO se bloquearán hasta que se abra la FIFO para escritura.
# Si se cierran los descriptores de lectura y escritura, los datos pendientes se descartan, aunque la FIFO permanece.
# Los datos tienen persistencia de proceso, las FIFO tienen persistencia de sistema de archivos.

# La lectura bloquea hasta que se escriba algo en la FIFO.
# La escritura bloquea hasta que se lea algo de la FIFO.
# Por lo tanto, se sincronizan los procesos.
# Si no queremos que se bloqueen, debemos abrir la FIFO en modo no bloqueante.