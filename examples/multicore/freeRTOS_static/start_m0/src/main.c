/** @brief This is a FreeRTOS application example with static memory allocation.
 */

/* NOTA: El stack de elementos dinámicos del RTOS está definido en RamLoc40_16! Ver heap_4.c
 * Solo importante si configSUPPORT_DYNAMIC_ALLOCATION no esta definido en FreeRTOSConfig.h
 * o fue seteado en 1. Si está en 0 no se utiliza el stack y esto carece de sentido */

/** \addtogroup FreeRTOS v9.0.0
 ** @{ */

/*==================[inclusions]=============================================*/

#include "../../../freeRTOS_static/start_m0/inc/main.h"

#include "../../../freeRTOS_static/start_m0/inc/FreeRTOSConfig.h"
#include "board.h"
#include "cr_start_m0.h"

#include "FreeRTOS.h"
#include "task.h"

/*==================[macros and definitions]=================================*/

 /* Dimensions the buffer that the task being created will use as its stack.
    NOTE:  This is the number of words the stack will hold, not the number of
    bytes.  For example, if each stack item is 32-bits, and this is set to 100,
    then 400 bytes (100 * 32-bits) will be allocated. */
#define STACK_SIZE 200

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

/* Structure that will hold the TCB of the task being created. */
__attribute__ ((section(".StackM4"))) static StaticTask_t xTaskBuffer1;

/* Buffer that the task being created will use as its stack.  Note this is
    an array of StackType_t variables.  The size of StackType_t is dependent on
    the RTOS port. For this one it is 32-bits */

__attribute__ ((section(".StackM4"))) static StackType_t xStack1[ STACK_SIZE ];

/* --------------------------- Stack SystickUpdate freeRTOS ---------------------------- */

__attribute__ ((section(".StackM4"))) static StaticTask_t xTaskBufferSystickUpdate;
__attribute__ ((section(".StackM4"))) static StackType_t xStackSystickUpdate[ STACK_SIZE ];

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	/* Start Cortex-M0 core */
	cr_start_m0(SLAVE_M0APP, (uint8_t *)0x1B000000); // le pasa la dirección de memoria en donde esta la imagen de la aplicación del Cortex-M0

	/* Enable IRQ for M0 Core */
	NVIC_EnableIRQ(M0APP_IRQn);
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

	xTaskCreateStatic(
					taskledCIAA, /* nombre de la tarea como se declaró */
					(const char *)"task", /* string descriptivo opcional */
					STACK_SIZE, /* tamaño de la pila */
					&t1, /* parámetro que le pasas a la función (void * a) -> comodín */
					1, /* prioridad (d2e 1 en adelante) */
					xStack1,	/* Array to use as the task's stack. */
					&xTaskBuffer1);  /* Variable to hold the task's data structure. */

	xTaskCreateStatic(
					vSystickUpdate, /* nombre de la tarea como se declaró */
					(const char *)"Refreshes Systick config", /* string descriptivo opcional */
					STACK_SIZE, /* tamaño de la pila */
					NULL, /* parámetro que le pasas a la función (void * a) -> comodín */
					3, /* prioridad (d2e 1 en adelante) */
					xStackSystickUpdate,	/* Array to use as the task's stack. */
					&xTaskBufferSystickUpdate);  /* Variable to hold the task's data structure. */

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
