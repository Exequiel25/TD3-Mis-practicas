/*

Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:

	1) Poseer dos tareas, Tarea1 y Tarea2, una cola de mansajes entre ellas y una rutina de atención de interrupción de timer RIT.
	2) La Tarea1 debe enviar elementos a la cola de mensajes cada 1500 ms.
	3) La Tarea2 debe esperar de la interrupción del timer RIT (que será de 3 segundo). Una vez que expira el timer, consumir un elemento, indicándolo por puerto serie el elemento consumido y cambiar el estado del led Amarillo.

BOARD: EDU CIAA

*/

#include "board.h"
#include "chip.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#define LED_AMARILLO 3

#define PRIO_TAREA1 2 // tarea periodica
#define PRIO_TAREA2 1

#define PERIOD_TAREA1 1500
#define PERIOD_TIMER 3000

SemaphoreHandle_t xSem_serie;
SemaphoreHandle_t xSem_port;
xQueueHandle xCola;

static void initHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
}

static void InitTimer(void)
{
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER, PERIOD_TIMER);
	Chip_RIT_Enable(LPC_RITIMER);
}

void RIT_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	Chip_RIT_ClearInt(LPC_RITIMER);
	// printf("Interrupcion\r\n");
	xSemaphoreGiveFromISR(xSem_serie, &xHigherPriorityTaskWoken);
	if (xHigherPriorityTaskWoken == pdTRUE)
	{
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		/* Si el semáforo ha despertado
		 una tarea , se fuerza un cambio
		 de contexto */
	}
}

void vTarea1(void *pvParameters)
{
	portTickType xPeriodicity = PERIOD_TAREA1 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	uint8_t dato = 0;

	while (1)
	{
		xSemaphoreTake(xSem_port, portMAX_DELAY);
		printf("Enviando...: %d\r\n", dato);
		xSemaphoreGive(xSem_port);
		if (xQueueSend(xCola, &dato, 0) == pdFAIL)
		{
			printf("Error al enviar dato a la cola\r\n");
		}
		dato++;
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void vTarea2(void *pvParameters)
{
	uint8_t dato = 0;

	while (1)
	{
		if (xSemaphoreTake(xSem_serie, portMAX_DELAY) == pdTRUE)
		{
			if (xQueueReceive(xCola, &dato, 0) == pdPASS)
			{
				xSemaphoreTake(xSem_port, portMAX_DELAY);
				printf("Leyendo...: %d\r\n", dato);
				xSemaphoreGive(xSem_port);
				Board_LED_Toggle(LED_AMARILLO);
			}
			else
			{
				printf("Error al recibir dato de la cola\r\n");
			}
		}
	}
}

int main(void)
{
	initHardware();

	printf("Ejercicio 2 - RTOS 2\r\n");

	xSem_serie = xSemaphoreCreateBinary();
	xSem_port = xSemaphoreCreateMutex();
	xSemaphoreGive(xSem_port);
	xCola = xQueueCreate(10, sizeof(uint8_t)); // cola de 10 elementos de 1 byte cada uno

	if (xSem_serie == NULL || xCola == NULL)
	{
		printf("Error al crear los semaforos y colas\r\n");
		while (1)
			;
	}

	xTaskCreate(vTarea1, (signed char *)"Tarea1", configMINIMAL_STACK_SIZE, NULL, PRIO_TAREA1, NULL);
	xTaskCreate(vTarea2, (signed char *)"Tarea2", configMINIMAL_STACK_SIZE, NULL, PRIO_TAREA2, NULL);

	InitTimer();
	NVIC_EnableIRQ(RITIMER_IRQn);
	NVIC_SetPriority(RITIMER_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

	vTaskStartScheduler();

	return 1;
}
