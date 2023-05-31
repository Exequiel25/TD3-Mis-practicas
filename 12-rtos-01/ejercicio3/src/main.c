/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar dos tareas, Tarea1 y Tarea2.
    2) La Tarea1, de mayor prioridad, debe ejecutar una espera activa (busy-waiting) indicando a través del puerto serie el valor de las entradas GPIO_0 a GPIO_3 en formato binario (nibble).
    3) Periódicamente debe aumentar la prioridad de la Tarea2, para que esta pueda ejecutarse.
    4) La Tarea2 debe cambiar el estado del led verde, indicarlo por puerto serie y disminuir su propia prioridad para detener su ejecución.

BOARD: EDU CIAA
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

// Prioridades de las tareas
#define TAREA1_PRIORIDAD (tskIDLE_PRIORITY + 2)
#define TAREA2_PRIORIDAD (tskIDLE_PRIORITY + 1)

// Periodo de la tarea 2
#define TAREA2_PERIODO pdMS_TO_TICKS(1000)

// LED a prender
#define LED_VERDE 5

// Prototipos de funciones
void tarea1(void *p);
void tarea2(void *p);

TaskHandle_t tarea2_handle;

// Funcion principal
int main(void)
{
   // Inicializaciones
   Board_Init();
   printf("Ejercicio 3 - RTOS 1\r\n");

   // Crear tareas
   xTaskCreate(tarea1, (const char *)"tarea1", configMINIMAL_STACK_SIZE * 2, NULL, TAREA1_PRIORIDAD, NULL);
   xTaskCreate(tarea2, "Tarea2", configMINIMAL_STACK_SIZE, NULL, TAREA2_PRIORIDAD, &tarea2_handle);

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
      printf("GPIO_0 a GPIO_3 en binario: %d%d%d%d\r\n", Board_GPIO_GetStatus(BOARD_GPIO_0), Board_GPIO_GetStatus(BOARD_GPIO_1), Board_GPIO_GetStatus(BOARD_GPIO_2), Board_GPIO_GetStatus(BOARD_GPIO_3));
      vTaskDelay(pdMS_TO_TICKS(100));
      vTaskPrioritySet(tarea2_handle, TAREA2_PRIORIDAD + 1);
   }
}

void tarea2(void *p)
{
   while (1)
   {
      // Toggle LED
      Board_LED_Toggle(LED_VERDE);
      // Imprimir estado LED
      printf("LED verde: %d\r\n", Board_LED_Test(LED_VERDE));
      // Disminuir prioridad
      vTaskPrioritySet(NULL, TAREA2_PRIORIDAD - 1);
      // Esperar 1 segundo
      vTaskDelay(TAREA2_PERIODO);
   }
}