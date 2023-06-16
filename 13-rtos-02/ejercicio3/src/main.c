/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

	1) Posea tres tareas, la Tarea1, Tarea2 y Tarea3.
	2) La Tarea1, debe tener la mayor prioridad, la Tarea2 media prioridad y Tarea3 baja prioridad.
	3) La Tarea1 y la Tarea3 comparten el puerto serie, enviando un mensaje cada una periodicamente, cada 800 ms.
	4) La Tarea2 es una tarea periódica, que ejecuta de manera contínua un bucle de busy waiting de 1 segundo aprox, luego cambia el led Rojo cada y genera un delay de 200 ms.
	5) Plantee su solución para evitar inversión de prioridad.

BOARD: EDU CIAA

*/

#include "board.h"
#include "chip.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#define LED_ROJO 3

#define PRIO_TAREA1 3
#define PRIO_TAREA2 2
#define PRIO_TAREA3 1

// en ms
#define PERIOD_TAREA1Y3 800
#define DELAY_TAREA2 200
#define DELAY_TAREA2_BUSY 1000

// Semaforo para puerto serie
SemaphoreHandle_t xSem_puerto_serie;

// prototipos de funciones
static void initHardware(void);
void vTarea1(void *pvParameters);
void vTarea2(void *pvParameters);
void vTarea3(void *pvParameters);

int main(void)
{
	initHardware();

	printf("Ejercicio 3 - RTOS 2\r\n");

	// Creacion de semaforo
	xSem_puerto_serie = xSemaphoreCreateBinary();
	xSemaphoreGive(xSem_puerto_serie);

	// Creacion de tareas
	xTaskCreate(vTarea1, (const char *)"tarea1", configMINIMAL_STACK_SIZE, NULL, PRIO_TAREA1, NULL);
	xTaskCreate(vTarea2, (const char *)"tarea2", configMINIMAL_STACK_SIZE, NULL, PRIO_TAREA2, NULL);
	xTaskCreate(vTarea3, (const char *)"tarea3", configMINIMAL_STACK_SIZE, NULL, PRIO_TAREA3, NULL);

	// Inicio de scheduler
	vTaskStartScheduler();

	// Nunca llega aca
	return 0;
}

static void initHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
}

void vTarea1(void *pvParameters)
{
	while (1)
	{
		xSemaphoreTake(xSem_puerto_serie, portMAX_DELAY);
		printf("Tarea 1\r\n");
		xSemaphoreGive(xSem_puerto_serie);
		vTaskDelay(pdMS_TO_TICKS(PERIOD_TAREA1Y3));
	}
}

void vTarea2(void *pvParameters)
{
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(DELAY_TAREA2));
		Board_LED_Toggle(LED_ROJO);
		vTaskDelay(pdMS_TO_TICKS(DELAY_TAREA2_BUSY));
	}
}

void vTarea3(void *pvParameters)
{
	while (1)
	{
		xSemaphoreTake(xSem_puerto_serie, portMAX_DELAY);
		printf("Tarea 3\r\n");
		xSemaphoreGive(xSem_puerto_serie);
		vTaskDelay(pdMS_TO_TICKS(PERIOD_TAREA1Y3));
	}
}
