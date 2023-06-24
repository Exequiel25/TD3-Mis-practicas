/*
Complete la función vTask1() de la aplicación FreeRTOS para que cumpla la siguiente consigna:

- Periódicamente, la tarea debe enviar por puerto serie el texto recibido como parámetro en su creación y bloquearse durante 800ms.
*/

#include "FreeRTOS.h"
#include "task.h"

int main(void)
{
    ...
}

void vTask1(void *pvParameters)
{
    char *pcTaskName;
    const TickType_t xDelay = pdMS_TO_TICKS(800);
    pcTaskName = (char *)pvParameters;
    for (;;)
    {
        vPrintString(pcTaskName);
        vTaskDelay(xDelay);
    }