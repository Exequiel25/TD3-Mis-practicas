/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

    1) Ejecutar las tareas Tarea1, Tarea2 y Tarea3 con los niveles de prioridad apropiados.
    2) Las tareas Tarea1 y Tarea2 deben enviar por cola de mensaje a la Tarea3 el tiempo en milisegundos que debe estar encendido el led amarillo e indicarlo por puerto serie.
    3) La Tarea3 debe leer esos tiempos de la cola a medida que llegan y controlar el led en cuestión. Siempre, el tiempo apagado del led es de 500 ms. También debe indicar por puerto serie sus acciones.
    4) Indique qué pasa en caso de que el timeout de la escritura en la cola de mensajes sea de 300 ms.

BOARD: EDU CIAA
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Prioridades de las tareas:
#define TAREA1_PRIORIDAD (tskIDLE_PRIORITY + 1)
#define TAREA2_PRIORIDAD (tskIDLE_PRIORITY + 1)
#define TAREA3_PRIORIDAD (tskIDLE_PRIORITY + 2)

// Periodo de la tarea 2
#define TAREA2_PERIODO pdMS_TO_TICKS(1000)

// LED a prender
#define LED_AMARILLO 3

// Crear cola de mensajes
QueueHandle_t cola;

// Prototipos de funciones
void tarea1(void *p);
void tarea2(void *p);
void tarea3(void *p);

// Función principal
int main(void)
{
   printf("Ejercicio 5 - RTOS 1\r\n");

   // Crear tarea 1
   xTaskCreate(tarea1,                       // Función de la tarea a ejecutar
               (const char *)"tarea1",       // Nombre de la tarea como String amigable para el usuario
               configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
               NULL,                         // Parametros de tarea
               TAREA1_PRIORIDAD,             // Prioridad de la tarea
               NULL                          // Puntero a la tarea creada en el sistema
   );

   // Crear tarea 2
   xTaskCreate(tarea2,                       // Función de la tarea a ejecutar
               (const char *)"tarea2",       // Nombre de la tarea como String amigable para el usuario
               configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
               NULL,                         // Parametros de tarea
               TAREA2_PRIORIDAD,             // Prioridad de la tarea
               NULL                          // Puntero a la tarea creada en el sistema
   );

   // Crear tarea 3
   xTaskCreate(tarea3,                       // Función de la tarea a ejecutar
               (const char *)"tarea3",       // Nombre de la tarea como String amigable para el usuario
               configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
               NULL,                         // Parametros de tarea
               TAREA3_PRIORIDAD,             // Prioridad de la tarea
               NULL                          // Puntero a la tarea creada en el sistema
   );

   // Crear cola de mensajes
   cola = xQueueCreate(1, sizeof(uint32_t));

   // Iniciar scheduler
   vTaskStartScheduler();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while (1)
   {
      // Si cae en este while 1 significa que no pudo iniciar el scheduler por falta de memoria
   }
   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

// Implementación de funciones
void tarea1(void *p)
{
   while (1)
   {
      // Enviar tiempo de encendido del led amarillo
      uint32_t tiempo = 1000;
      // xQueueSend(cola, &tiempo, portMAX_DELAY); // Espera a max delay
      if (xQueueSend(cola, &tiempo, 300 / portTICK_PERIOD_MS) != pdPASS) // timeout de 300 ms
      {
         // Manejar el error adecuadamente
         printf("Tarea 1: Error al enviar tiempo de encendido del led amarillo\r\n");
      }
      printf("Tarea 1: Enviado tiempo de encendido del led amarillo: %d ms\r\n", tiempo);

      // Esperar 500 ms
      vTaskDelay(pdMS_TO_TICKS(500));
   }
}

void tarea2(void *p)
{
   while (1)
   {
      // Enviar tiempo de encendido del led amarillo
      uint32_t tiempo = 2000;
      // xQueueSend(cola, &tiempo, portMAX_DELAY); // Espera a max delay
      if (xQueueSend(cola, &tiempo, 300 / portTICK_PERIOD_MS) != pdPASS) // timeout de 300 ms
      {
         // Manejar el error adecuadamente
         printf("Tarea 2: Error al enviar tiempo de encendido del led amarillo\r\n");
      }
      printf("Tarea 2: Enviado tiempo de encendido del led amarillo: %d ms\r\n", tiempo);

      // Esperar 1 segundo
      vTaskDelay(TAREA2_PERIODO);
   }
}

void tarea3(void *p)
{
   while (1)
   {
      // Leer tiempo de encendido del led amarillo
      uint32_t tiempo;
      if (xQueueReceive(cola, &tiempo, pdMS_TO_TICKS(300)) == pdTRUE)
      {
         // Prender led amarillo
         Board_LED_Set(LED_AMARILLO, true);
         printf("Tarea 3: Prendido led amarillo\r\n");

         // Esperar tiempo de encendido
         vTaskDelay(pdMS_TO_TICKS(tiempo));

         // Apagar led amarillo
         Board_LED_Set(LED_AMARILLO, false);
         printf("Tarea 3: Apagado led amarillo\r\n");
      }
      else
      {
         printf("Tarea 3: Error al recibir tiempo de encendido del led amarillo\r\n");
      }

      // Esperar 500 ms
      vTaskDelay(pdMS_TO_TICKS(500));
   }
}
