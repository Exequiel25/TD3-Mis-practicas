/*
Complete la aplicación FreeRTOS para que cumpla las siguientes consignas:

1- Utilizando un mecanismo de sincronización, vTask1 debe cambiar el estado del LED verde cuando se recibe una interrupción del RIT.
2- vTask1 debe esperar indefinidamente la señal de sincronización.
3- vTask1 es de alta prioridad. vTask 2 ejecuta una espera activa de baja prioridad.
*/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xMutex;
int main(void)
{
    ...
}

void vTask1(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(1000);
    for (;;)
    {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE)
        {
            Board_LED_Toggle(5);      // LED verde
            else Board_LED_Toggle(4); // LED rojo
        }
    }
}
void vTask2(void *pvParameters)
{
    for (;;)
    {
        vPrintString("Espera activa\r\n");
    }
}

void RIT_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    Chip_RIT_ClearInt(LPC_RITIMER);
}