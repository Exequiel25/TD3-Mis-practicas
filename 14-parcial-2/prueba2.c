/*
Complete la aplicación FreeRTOS para que cumpla las siguientes consignas:
1- Posea una tarea vTask1 que se ejecute de manera continua e informe este estado por el puerto serie.
2- vTask1 se debe crear en primer lugar.
3- Posea una tarea vTask2 que pase a estado "Lista" exactamente cada 750ms y cambie el estado del LED verde.
*/

#include "FreeRTOS.h"
#include "task.h"

int main(void)
{
    xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vTask2, "vTask2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
    vTaskStartScheduler();
    for (;;)
    {
    }
}

void vTask1(void *pvParameters)
{
    for (;;)
    {
        vPrintString("Task 1 is running\r\n");
    }
}

void vTask2(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(750);
    for (;;)
    {
        Board_LED_Toggle(5);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
