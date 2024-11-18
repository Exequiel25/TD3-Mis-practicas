/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar dos tareas, Tarea1 y Tarea2, con los niveles de prioridad apropiados.
    2) La Tarea1 debe ejecutarse de manera continua, indicando a través del puerto serie el valor de la entrada GPIO_0.
    3) La Tarea2 debe ser periódica, con período de 1 segundo y debe cambiar el estado del led verde e indicarlo a través del puerto serie. Adicionalmente debe indicar los ticks del reloj de FreeRTOS para verificar el período solicitado.

BOARD: EDU CIAA
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

// Prioridades de las tareas
#define TAREA1_PRIORIDAD (tskIDLE_PRIORITY + 1)
#define TAREA2_PRIORIDAD (tskIDLE_PRIORITY + 2)

// Periodo de la tarea 2
#define TAREA2_PERIODO pdMS_TO_TICKS(1000)

// LED a prender
#define LED_VERDE 5

// Prototipos de funciones
void vTarea1(void *p);
void vTarea2(void *p);

// Funcion principal
int main(void)
{
   printf("Ejercicio 1 - RTOS 1\r\n");

   // Crear tareas
   xTaskCreate(vTarea2, (const char *)"tarea2", configMINIMAL_STACK_SIZE, NULL, TAREA2_PRIORIDAD, NULL);
   xTaskCreate(vTarea1, (const char *)"tarea1", configMINIMAL_STACK_SIZE, NULL, TAREA1_PRIORIDAD, NULL);

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
void vTarea1(void *p)
{
   while (1)
   {
      printf("GPIO_0: %d\r\n", Board_GPIO_GetStatus(BOARD_GPIO_0)); // Leer GPIO_0
      vTaskDelay(pdMS_TO_TICKS(500));                               // Esperar 500 ms
   }
}

void vTarea2(void *p)
{
   TickType_t xLastWakeTime = xTaskGetTickCount(); // Iniciar contador de ticks
   while (1)
   {
      Board_LED_Toggle(LED_VERDE);                             // Cambiar estado del led verde
      printf("Tarea2: %d\r\n", xLastWakeTime);                 // Imprimir tick actual
      printf("Estado LED: %d\r\n", Board_LED_Test(LED_VERDE)); // Imprimir estado del led
      vTaskDelayUntil(&xLastWakeTime, TAREA2_PERIODO);
   }
}
