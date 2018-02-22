/** @brief This is a FreeRTOS application example with dynamic memory allocation.
 */

/** \addtogroup FreeRTOS v9.0.0
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"

#include "FreeRTOSConfig.h"
#include "board.h"

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

taskData t1 = {0, 900};

/*==================[FreeRTOS static elements stack]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();

/* Configures and associates the uC RIT to the freeRTOS tick */
	prvSetupTimerInterrupt();

    /* Enable IRQ for M4 Core */
    NVIC_EnableIRQ(M4_IRQn);
}

/*==================[interrupt handling]==========================*/

void MX_CORE_IRQHandler(void)
{
	/* limpiamos el evento seteado por el core remoto */
	LPC_CREG->M4TXEVENT = 0;   /* ACK */

	/*
	 * 	Codigo super X8
	 */
}

/*==================[tasks definition]==========================*/

static void taskledCIAA(void * a)
{
	taskData * t = (taskData *) a; /* el puntero a void es un comodín. Hay que si o si castearlo para que funcione */
	while (1) {
		Board_LED_Toggle(t->numbled);
		vTaskDelay((t->tiempo) / portTICK_RATE_MS);
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

	vTaskStartScheduler();

	while(1)
	{
		/*
		 *	Infinite loop
		 */
	}

}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
