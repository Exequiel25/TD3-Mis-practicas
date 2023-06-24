/*
Complete la aplicación FreeRTOS para que cumpla las siguientes consignas:

    1- Posea una tarea única con la prioridad más alta posible.
    2- La tarea debe cambiar el estado del LED rojo, enviar por puerto serie el texto enviado como parámetro en su creación y bloquearse durante 800ms.
*/

#include "FreeRTOS.h"
#include "task.h"

const char *pvTaskParameters = "Tarea 1 en ejecución\r\n";

int main(void)
{
    // Crear tarea
    xTaskCreate(
        vTask1,                   // Función de la tarea a ejecutar
        "Tarea 1",                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, // Cantidad de stack de la tarea
        (void *)pvTaskParameters, // Parametros de tarea
        tskIDLE_PRIORITY + 3,     // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL                      // Puntero a la tarea creada en el sistema
    );

    // Iniciar scheduler
    vTaskStartScheduler();

    // ---------- REPETIR POR SIEMPRE --------------------------
    while (TRUE)
    {
        // Si cae en este while 1 significa que no pudo iniciar el scheduler por falta de memoria
    }
    // ----------------------------------------------------------
}

void vTask1(void *pvParameters)
{
    char *pcTaskName;
    const TickType_t xDelay = pdMS_TO_TICKS(800);
    pcTaskName = (char *)pvParameters;
    for (;;)
    {
        vPrintString(pcTaskName);
        Board_LED_Toggle(4); // LED rojo;
        vTaskDelay(xDelay);
    }
}
