/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar dos tareas, Tarea1 y Tarea2, con los niveles de prioridad apropiados y un mecanismo de sincronización.
    2) La Tarea1 debe ejecutar de manera contínua un bucle de busy waiting de 1 segundo aprox, indicándo este estado a través del puerto serie.
    3) La Tarea2 debe estar serializada, bloqueada hasta que la Tarea1 complete su loop, una vez que pase esto, debe cambiar el estado del led Azul
    4) Justifique que herramienta de sincronización utilizó.

BOARD: EDU CIAA

*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define LED_AZUL 2

SemaphoreHandle_t xMutex;

void vTarea1(void *pvParameters)
{
   while (1)
   {
      // Tomar mutex
      xSemaphoreTake(xMutex, portMAX_DELAY);

      printf("Tarea1: ejecutando Busy Waiting\r\n");

      // Liberar mutex
      xSemaphoreGive(xMutex);

      // Delay 1 segundo
      vTaskDelay(pdMS_TO_TICKS(1000));
   }
}

void vTarea2(void *pvParameters)
{
   while (1)
   {
      // Tomar mutex
      xSemaphoreTake(xMutex, portMAX_DELAY);

      printf("Tarea2: Cambiando estado del LED AZUL\r\n");
      Board_LED_Toggle(LED_AZUL);

      // Liberar mutex
      xSemaphoreGive(xMutex);

      // Delay 1 segundo
      vTaskDelay(pdMS_TO_TICKS(1000)); // necesaria para que la tarea 1 pueda tomar el mutex
   }
}

void main()
{
   printf("Ejercicio 1 - RTOS 2\r\n");

   // Create mutex
   xMutex = xSemaphoreCreateMutex();

   // Create Tarea1 and Tarea2
   xTaskCreate(vTarea1, "tarea1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
   xTaskCreate(vTarea2, "tarea2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

   // Start scheduler
   vTaskStartScheduler();
}
