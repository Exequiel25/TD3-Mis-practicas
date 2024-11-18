/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar dos tareas, Tarea1 y Tarea2 de distinta prioridad y que sean implementadas con la misma función.
    2) Ambas tareas deben indicar por puerto serie que están en ejecución y su prioridad, luego bloquearse por 500 ms.
    3) En el tiempo ocioso (Idle) aprovechar para cambiar el estado del led azul cada 300 ms e indicarlo por puerto serie. (Implementar Idle Hook)
    4) Justifique qué sucede con los cambios de estado del led en caso que la tarea Tarea1 pase a ejecutarse de manera contínua.

BOARD: EDU CIAA
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

// Prioridades de las tareas
#define TAREA1_PRIORIDAD (tskIDLE_PRIORITY + 2)
#define TAREA2_PRIORIDAD (tskIDLE_PRIORITY + 1)

// Tiempo espera de las tareas
#define TAREAS_PERIODO pdMS_TO_TICKS(500)
#define LED_PERIODO pdMS_TO_TICKS(300)

// LED a prender
#define LED_AZUL 2

// Prototipos de funciones
void vTarea(void *p);
void vApplicationIdleHook(void);

// Funcion principal
int main(void)
{
   printf("Ejercicio 4 - RTOS 1\r\n");

   // Crear tareas
   xTaskCreate(vTarea, (const char *)"tarea1", configMINIMAL_STACK_SIZE, NULL, TAREA1_PRIORIDAD, NULL);
   xTaskCreate(vTarea, (const char *)"tarea2", configMINIMAL_STACK_SIZE, NULL, TAREA2_PRIORIDAD, NULL);

   // Iniciar scheduler
   vTaskStartScheduler();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while (1)
   {
   }
   // NO DEBE LLEGAR NUNCA AQUI
   return 0;
}

// Implementacion de funciones
void vTarea(void *p)
{
   while (1)
   {
      // Indicar por puerto serie que la tarea esta en ejecucion
      printf("Tarea %s en ejecucion con prioridad %d\r\n", pcTaskGetName(NULL), uxTaskPriorityGet(NULL));

      // Bloquear tarea por 500 ms
      vTaskDelay(TAREAS_PERIODO);
   }
}

void vApplicationIdleHook(void)
{

   TickType_t xLastWakeTime = xTaskGetTickCount();
   TickType_t xWakeTime;

   while (1)
   {
      xWakeTime = xTaskGetTickCount();
      if (xWakeTime - xLastWakeTime > 300)
      {
         xLastWakeTime = xWakeTime;
         // Cambiar estado del led azul
         Board_LED_Toggle(LED_AZUL);

         // Indicar por puerto serie que la tarea esta en ejecucion
         printf("Tarea Idle en ejecucion\r\n");
      }
   }
}
