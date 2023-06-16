/*

Reescriba el código mostrado en la sección 4.5.6 (página 105) del libro Sistemas Empotrados en Tiempo Real usando el sistema operativo FreeRTOS. Use para todos los semáforos un timeout de 1000 ms. Describa la ejecución de ambas tareas suponiendo que inicialmente ambos semáforos están libres, que inicialmente se ejecuta la Tarea1 y que se produce un cambio de contexto justo antes de que la Tarea1 pida el semáforo B. Ilustre esta descripción mediante un diagrama similar al mostrado en la figura 4.4.

BOARD: EDU CIAA

4.5.6. Abrazo mortal (Deadlock)

*/

#include "board.h"
#include "chip.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

int a, b; // Variables compartidas

// Handlers semaforos
SemaphoreHandle_t semA;
SemaphoreHandle_t semB;

// Prototipos de funciones
void vTarea1(void *pvParameters);
void vTarea2(void *pvParameters);

int main()
{
    // Inicializaciones
    SystemCoreClockUpdate();
    Board_Init();

    printf("Ejercicio 5 - RTOS 2\r\n");

    // Creacion de semaforos
    semA = xSemaphoreCreateBinary();
    semB = xSemaphoreCreateBinary();

    // Creacion de tareas
    xTaskCreate(vTarea1, (const char *)"vTarea1", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *)NULL);
    xTaskCreate(vTarea2, (const char *)"vTarea2", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *)NULL);

    // Iniciar el planificador
    vTaskStartScheduler();

    for (;;)
        ;
    return 0;
}

void vTarea1(void *pvParameters)
{
    while (1)
    {
        // Tomar ambos semaforos
        xSemaphoreTake(semA, portMAX_DELAY);
        xSemaphoreTake(semB, portMAX_DELAY);
        a = b;
        printf("Soy 1: a = %d, b = %d\r\n", a, b);
        // Liberar ambos semaforos
        xSemaphoreGive(semA);
        xSemaphoreGive(semB);
    }
}

void vTarea2(void *pvParameters)
{
    while (1)
    {
        // Tomar ambos semaforos
        xSemaphoreTake(semA, portMAX_DELAY);
        xSemaphoreTake(semB, portMAX_DELAY);
        b = a;
        printf("Soy 2: a = %d, b = %d\r\n", a, b);
        // Liberar ambos semaforos
        xSemaphoreGive(semA);
        xSemaphoreGive(semB);
    }
}
