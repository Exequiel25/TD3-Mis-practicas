#!/bin/env sh

gcc -o sig_01 sig_01.c
./sig_01

echo $?
echo "Estado de salida (exit status)"

# Si termina en forma normal, el exit status es 5
# debido a que escribimos en el código sig_01.c
# un exit(5)

# Cuando interrumpimos el proceso con Ctrl+C,
# exit status indica un valor de 130 indicando
# que el proceso termino de forma abrupta

# Una señal es una notificación entregada a un proceso debido a un evento asincrónico.
# Las señales son utilizadas para notificar eventos como errores, terminación de procesos,
# etc. Las señales son enviadas a un proceso por el kernel del sistema operativo.
# Son como interrupciones de software (interrumpen el flujo normal de ejecución de un programa).

# Si el proceso tiene permisos adecuados, puede enviar una señal a otro proceso.
# Se utilizan para:
# 1. Técnicas de sincronización.
# 2. Comunicación primitiva entre procesos.

# Eventos que generan señales por el kernel:
# 1. Errores de hardware (ejemplo división por 0).
# 2. Errores de software (ejemplo violación de segmento).
# 3. El usuario presiona Ctrl+C, o suspende el proceso con Ctrl+Z.
# 4. Evento de software (ejemplo terminación de un proceso hijo, expiración de timer, etc.).

# Tipos de señales comunes:
# 2. SIGINT: Interrupción del proceso (Ctrl+C).
# 9. SIGKILL: Terminación del proceso (no se puede ignorar).
# 15. SIGTERM: Terminación del proceso (se puede ignorar).
# 19. SIGSTOP: Detiene el proceso (no se puede ignorar).
# 18. SIGCONT: Continúa la ejecución del proceso detenido.
# 17. SIG_CHLD: Señal enviada al padre cuando un proceso hijo termina.
# 10. SIGUSR1: Señal definida por el usuario.
# SIG_DFL: Restaura la acción por defecto de la señal.
# SIG_IGN: Ignora la señal.

# Si se ejecuta int kill (pid_t pid, int sig), se tiene:
# pid: Identificador del proceso al cual se le enviará la señal.
# sig: Número de la señal a enviar.
# Si:
# pid > 0: Se envía la señal al proceso con identificador pid.
# pid = 0: Se envía la señal a todos los procesos del mismo grupo del proceso que envía la señal.
# pid = -1: Se envía la señal a todos los procesos para los cuales el proceso que envía la señal tiene permisos para enviar señales.
# pid < -1: Se envía la señal a todos los procesos del grupo -pid.
# pid = 1: Se envía la señal a todos los procesos a los cuales tiene permiso de enviar (todos menos init y él mismo).


# Función como puntero:
# void funcion_ejemplo(int a) { printf("a = %d\n", a); }
# int main() { void (*funcion)(int) = &funcion_ejemplo; (*funcion)(5); return 0; }