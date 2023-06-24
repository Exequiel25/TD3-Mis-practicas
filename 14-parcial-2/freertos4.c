/*
Complete la aplicación FreeRTOS para que cumpla las siguientes consignas:
- Utilizando un mecanismo de sincronización, vTask1 debe cambiar el estado del LED verde cuando se recibe una interrupción del RIT.
- vTask1 debe esperar la señal de sincronización durante 1 segundo.
- vTask1 es de alta prioridad. vTask 2 ejecuta una espera activa de baja prioridad.
*/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/********************************************************************************/
SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xMutex;

int main(void)
{
    // Crear tarea
    xTaskCreate(
        vTask1,                   // Función de la tarea a ejecutar
        "Tarea 1",                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, // Cantidad de stack de la tarea
        NULL,                     // Parametros de tarea
        tskIDLE_PRIORITY + 3,     // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL                      // Puntero a la tarea creada en el sistema
    );

    xTaskCreate(
        vTask2,                   // Función de la tarea a ejecutar
        "Tarea 2",                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, // Cantidad de stack de la tarea
        NULL,                     // Parametros de tarea
        tskIDLE_PRIORITY + 2,     // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL                      // Puntero a la tarea creada en el sistema
    );

    // Crear semaforos
    xBinarySemaphore = xSemaphoreCreateBinary();
    xMutex = xSemaphoreCreateMutex();

    // Iniciar scheduler
    vTaskStartScheduler();

    // ---------- REPETIR POR SIEMPRE --------------------------
    while (TRUE)
    {
        // Si cae en este while 1 significa que no pudo iniciar el scheduler por falta de memoria
    }
    // ----------------------------------------------------------
}

/********************************************************************************/
void vTask1(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(1000);
    for (;;)
    {
        if (xSemaphoreTake(xBinarySemaphore, xDelay) == pdTRUE)
            Board_LED_Toggle(5); // LED verde
        else
            Board_LED_Toggle(4); // LED rojo
    }
}
/********************************************************************************/
void vTask2(void *pvParameters)
{
    for (;;)
    {
        vPrintString("Espera activa\r\n");
    }
}
/********************************************************************************/
void RIT_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    Chip_RIT_ClearInt(LPC_RITIMER);
}
/********************************************************************************/