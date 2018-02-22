/** @brief This is a FreeRTOS application example with dynamic memory allocation.
 */

/** \addtogroup FreeRTOS v9.0.0
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"

#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string.h>

#include "Ciaa_Buttons.h"
#include "FreeRTOSConfig.h"
#include "ipc.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

__attribute__ ((section(".AHB_ETB16"))) static uint8_t arraytest[512];

/* --------------------------- IPC ---------------------------- */

__attribute__ ((section(".ipcM0"))) ipcrb_t ipcsend;
__attribute__ ((section(".ipcM0"))) static uint8_t ipcbufsend[sizeof(ipcmsg_t) * MAX_MSG];

__attribute__ ((section(".ipcM4"))) ipcrb_t ipcreceive;
__attribute__ ((section(".ipcM4"))) static uint8_t ipcbufreceive[sizeof(ipcmsg_t) * MAX_MSG];

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

static void SendIPCMsg(void);

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

	Ciaa_Buttons_Init();
	IPC_CreateStatic(&ipcsend, ipcbufsend);

/* Configures and associates the uC RIT to the freeRTOS tick */
	prvSetupTimerInterrupt();

}

static void SendIPCMsg(void)
{
	memset(arraytest, 0, sizeof(512));
	strcpy((char*)arraytest, "Test Cola IPC - Sase2017");

	ipcmsg_t msg;
	memset(&msg, 0, sizeof(ipcmsg_t));

	msg.senderid_t.cid = M0;
	msg.senderid_t.pid = Tarea1;
	msg.opcode = Code1;
	msg.operand[0] = (operand_t) arraytest;
	msg.operand[1] = sizeof(arraytest);

	IPC_SendMsg(&ipcsend ,&msg);
}

/*==================[interrupt handling]==========================*/

/*==================[tasks definition]==========================*/

static void taskledCIAA(void * a)
{
	taskData * t = (taskData *) a; /* el puntero a void es un comodín. Hay que si o si castearlo para que funcione */
	while (1) {
		Board_LED_Toggle(t->numbled);
		vTaskDelay((t->tiempo) / portTICK_RATE_MS);
	}
}

static void ButtonPolling(void * a)
{
	buttonstecnum_t tec = (buttonstecnum_t) a; /* el puntero a void es un comodín. Hay que si o si castearlo para que funcione */

	while(1)
	{
		if(Ciaa_Buttons_GetStatus() == tec)
		{
			/* Rutina antirebote */
			vTaskDelay(100 / portTICK_RATE_MS);
			if(Ciaa_Buttons_GetStatus() == tec)
			{
				/* Enviamos el mensaje a la cola y enviamos evento al core remoto */
				SendIPCMsg();
				__SEV();

				while(Ciaa_Buttons_GetStatus() != 0)
				{
					vTaskDelay(10 / portTICK_RATE_MS);
				}
			}
		}
	}
}

/*==================[external functions definition]==========================*/

int main(void)
{
	initHardware();

	buttonstecnum_t tec = TEC1;

	xTaskCreate(
				taskledCIAA, /* nombre de la tarea como se declaró */
			    (const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				&t1, /* parámetro que le pasas a la función (void * a) -> comodín */
				tskIDLE_PRIORITY+1, /* prioridad (d2e 1 en adelante) */
				0);

	xTaskCreate(
				ButtonPolling, /* nombre de la tarea como se declaró */
				(const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				(void *) tec, /* parámetro que le pasas a la función (void * a) -> comodín */
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
