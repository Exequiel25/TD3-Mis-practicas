/*
Complete la aplicación FreeRTOS para que cumpla las siguientes consignas:
1- La tarea vTask1 debe enviar a través de una cola de mensajes LIFO el valor entero 123 de manera continua.
2- En el caso de que la cola esté llena, vTask1 se debe bloquear durante 1 segundo.
3- La tarea vTask2 debe recibir los datos enviados por vTask1.
4- En el caso de que la cola esté vacía, vTask2 se debe bloquear durante 500ms.
*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xQueue;

int main(void)
{

    UBaseType_t uxQueueLength = 10;
    UBaseType_t uxItemSize = sizeof(int32_t);
    xQueue = xQueueCreate(uxQueueLength, uxItemSize);
    for (;;)
    {
    }
}

void vTask1(void *pvParameters)
{
    int32_t ValueToSend = 123;
    const TickType_t xDelay = pdMS_TO_TICKS(1000);

    for (;;)
    {
        xQueueSend(xQueue, &ValueToSend, xDelay);
    }
}

void vTask2(void *pvParameters)
{
    int32_t ReceivedValue;
    const TickType_t xDelay = pdMS_TO_TICKS(500);

    for (;;)
    {
        xQueueReceive(xQueue, &ReceivedValue, xDelay);
        vPrintString("Received value: ");
    }
}
