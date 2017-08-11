/** @brief This is a FreeRTOS application example with dynamic memory allocation.
 */

/** \addtogroup FreeRTOS v9.0.0 with intercore communication example (Core_M4)
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"

#include "FreeRTOSConfig.h"
#include "board.h"
#include "cr_start_m0.h"

#include "FreeRTOS.h"
#include "task.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/*==================[internal data definition]===============================*/

typedef struct taskData{
	uint8_t numbled;
	uint32_t tiempo;
}taskData;

taskData t1 = {5, 100};

/*==================[FreeRTOS static elements stack]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	/* Start Cortex-M0 core */
	cr_start_m0(SLAVE_M0APP, (uint8_t *)0x1B000000); // le pasa la dirección de memoria en donde esta la imagen de la aplicación del Cortex-M0

}

/*==================[interrupt handling]==========================*/

/*==================[tasks definition]==========================*/

static void taskledCIAA(void * a)
{
	taskData * t = (taskData *) a; /* el puntero a void es un comodín. Hay que castearlo para que funcione */

	while (1) {
		Board_LED_Toggle(t->numbled);
		vTaskDelay((t->tiempo) / portTICK_RATE_MS);
	}
}

static void vSystickUpdate(void * a)
{
	/* Execute after 1ms */
	vTaskDelay(1 / portTICK_RATE_MS);

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	while (1)
	{
		 vTaskSuspend(NULL);
	}
}

/*==================[external functions definition]==========================*/

int main(void)
{
	initHardware();

	xTaskCreate(
				taskledCIAA, /* nombre de la tarea como se declaró */
				(const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				&t1, /* parámetro que le pasas a la función (void * a) -> comodín */
				tskIDLE_PRIORITY+1, /* prioridad (d2e 1 en adelante) */
				0);

	xTaskCreate(
				vSystickUpdate, /* nombre de la tarea como se declaró */
				(const char *)"Refreshes Systick config", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				0, /* parámetro que le pasas a la función (void * a) -> comodín */
				tskIDLE_PRIORITY+1, /* prioridad (d2e 1 en adelante) */
				0);

	vTaskStartScheduler();

	while (1)
	{
		/*
		 *	Infinite loop
		 */
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
