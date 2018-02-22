/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a FreeRTOS Static application with intercore communication.
 * See http://www.freertos.org/Static_Vs_Dynamic_Memory_Allocation.html for help
 * with creating static FreeRTOS elements
 */

/* NOTA: El stack de elementos dinámicos del RTOS está definido en RamLoc40_16! Ver heap_4.c
 * Solo importante si configSUPPORT_DYNAMIC_ALLOCATION no esta definido en FreeRTOSConfig.h
 * o fue seteado en 1. Si está en 0 no se utiliza el stack y esto carece de sentido */

/** \addtogroup FreeRTOS v9.0.0 with intercore communication example (Core_M4)
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"

#include "FreeRTOSConfig.h"
#include "ipc.h"
#include "board.h"
#include "cr_start_m0.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

static SemaphoreHandle_t xSemaphoreIRQ;

/* --------------------------- IPC ---------------------------- */

__attribute__ ((section(".ipcM4"))) ipcrb_t ipcsend;
__attribute__ ((section(".ipcM4"))) static uint8_t ipcbufsend[sizeof(ipcmsg_t) * MAX_MSG];

__attribute__ ((section(".ipcM0"))) ipcrb_t ipcreceive;
__attribute__ ((section(".ipcM0"))) static uint8_t ipcbufreceive[sizeof(ipcmsg_t) * MAX_MSG];

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

uint8_t numled = 4;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	IPC_CreateStatic(&ipcreceive, ipcbufreceive);

	/* Start Cortex-M0 core */
	cr_start_m0(SLAVE_M0APP, (uint8_t *)0x1B000000); // le pasa la dirección de memoria en donde esta la imagen de la aplicación del Cortex-M0

	/* Enable IRQ for M0 Core */
	NVIC_EnableIRQ(M0APP_IRQn);
}

/*==================[interrupt handling]==========================*/

void M0APP_IRQHandler(void)
{
	/* Clear the event created by the remote core */
	LPC_CREG->M0APPTXEVENT = 0;   /* ACK */

	/* Disable IRQ for M0 Core while it's being handled */
	NVIC_DisableIRQ(M0APP_IRQn);

	long lHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR( xSemaphoreIRQ, &lHigherPriorityTaskWoken );
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken ); /* depends on the port for the uC being used
	more info -> "http://www.freertos.org/FAQISR.html" */
}

/*==================[tasks definition]==========================*/

static void taskledCIAA(void * a)
{
	taskData * t = (taskData *) a; /* el puntero a void es un comodín. Hay que castearlo para que funcione */

	while (1) {
		Board_LED_Toggle(t->numbled);
		vTaskDelay((t->tiempo) / portTICK_RATE_MS);
	}
}

static void taskM0IRQHandler(void * a)
{
	uint8_t * numled = (uint8_t *) a; /* el puntero a void es un comodín. Hay que castearlo para que funcione */
	ipcmsg_t msg;
	uint8_t * ptr;

	xSemaphoreIRQ = xSemaphoreCreateBinary();

	if( xSemaphoreIRQ == NULL )
	{
		while(1)
		{
			/* There was insufficient FreeRTOS heap available for the semaphore to
		be created uartd_successfully. */
		}
	}

	while (1) {
		xSemaphoreTake( xSemaphoreIRQ , portMAX_DELAY ); /* Semaphore blocks indefinitely */

		if(IPC_MsgWaiting(&ipcreceive))
		{
			memset(&msg, 0, sizeof(ipcmsg_t));

			IPC_Pop(&ipcreceive, &msg);
			ptr = msg.operand[0];
		}

		/* Enable IRQ for M0 Core */
		NVIC_EnableIRQ(M0APP_IRQn);
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
				taskM0IRQHandler, /* nombre de la tarea como se declaró */
				(const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				&numled, /* parámetro que le pasas a la función (void * a) -> comodín */
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
