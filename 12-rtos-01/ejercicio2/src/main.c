/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar la tarea Tarea1.
    2) La Tarea1 debe leer el valor de la entrada GPIO_2 cada 500 ms, indicando su estado por puerto serie. En caso de estar activa, crear la Tarea2.
    3) La Tarea2 debe cambiar el estado del led amarillo, indicarlo por puerto serie y terminar.

BOARD: EDU CIAA
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

// Prioridades de las tareas
#define TAREA1_PRIORIDAD (tskIDLE_PRIORITY + 1)
#define TAREA2_PRIORIDAD (tskIDLE_PRIORITY + 2)

// Periodo de la tarea 2
#define TAREA2_PERIODO pdMS_TO_TICKS(500)

// LED a prender
#define LED_AMARILLO 3

// Prototipos de funciones
void tarea1(void *p);
void tarea2(void *p);

// Funcion principal
int main(void)
{
   printf("Ejercicio 2 - RTOS 1\r\n");

   // Crear tarea 1
   xTaskCreate(tarea1, (const char *)"tarea1", configMINIMAL_STACK_SIZE * 2, NULL, TAREA1_PRIORIDAD, NULL);

   // Iniciar scheduler
   vTaskStartScheduler();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while (1)
   {
   }
   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontrolador y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

// Implementacion de funciones
void tarea1(void *p)
{
   while (1)
   {
      uint8_t valor = Board_GPIO_GetStatus(BOARD_GPIO_2);
      printf("GPIO_2: %d\r\n", valor); // Leer GPIO_0

      if (valor == 1)
      {
         xTaskCreate(tarea2, (const char *)"tarea2", configMINIMAL_STACK_SIZE * 2, NULL, TAREA2_PRIORIDAD, NULL);
      }

      vTaskDelay(pdMS_TO_TICKS(500)); // Esperar 500 ms
   }
}

void tarea2(void *p)
{
   Board_LED_Toggle(LED_AMARILLO);                                      // Cambiar estado del led amarillo
   printf("Estado LED AMARILLO: %d\r\n", Board_LED_Test(LED_AMARILLO)); // Imprimir estado del led
   vTaskDelete(NULL);                                                   // Eliminar tarea
}
