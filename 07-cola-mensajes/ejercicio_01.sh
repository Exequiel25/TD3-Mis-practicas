#!/bin/env sh

gcc -o mq01 mq01.c -lrt
./mq01

# Cola de mensajes:
# Comunicación entre procesos mediante unidades de mensajes.
# Los mensajes se almacenan en una cola de mensajes.
# La cola de mensajes es un área de memoria del kernel.

# Pueden leer procesos no relacionados, conocen identificador de la cola.
# Cuando un proceso lee un mensaje, este se elimina de la cola.
# Los mensajes se ordenan por prioridad, y luego por orden de llegada.
# Se pueden abrir como bloqueantes o no bloqueantes.
# La cola de mensaje tiene persistencia en kernel.

# Sincronización:
# La lectura bloquea hasta que se escriba algo en la cola.
# La escritura bloquea hasta que se lea algo de la cola.

# Para evitar cargar el stack, la estructura de la cola de mensajes se envía por referencia.
