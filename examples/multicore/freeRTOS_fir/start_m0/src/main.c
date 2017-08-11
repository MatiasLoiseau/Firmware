/** @brief This is a FreeRTOS application example with dynamic memory allocation.
 */

/* NOTA: El stack de elementos dinámicos del RTOS está definido en RamLoc40_16! Ver heap_4.c
 * Solo importante si configSUPPORT_DYNAMIC_ALLOCATION no esta definido en FreeRTOSConfig.h
 * o fue seteado en 1. Si está en 0 no se utiliza el stack y esto carece de sentido */

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

static void SendIPCMsg_ProcessingComplete(float * ptr, uint32_t nsamples);

static void FIR_Filter(float * ptr, uint32_t nsamples);

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

	IPC_CreateStatic(&ipcsend, ipcbufsend);
	IPC_CreateStatic(&ipcreceive, ipcbufreceive);

	/* Start Cortex-M0 core */
	cr_start_m0(SLAVE_M0APP, (uint8_t *)0x1B000000); // le pasa la dirección de memoria en donde esta la imagen de la aplicación del Cortex-M0

	/* Enable IRQ for M0 Core */
	NVIC_EnableIRQ(M0APP_IRQn);
}

static void SendIPCMsg_ProcessingComplete(float * ptr, uint32_t nsamples)
{
	ipcmsg_t msg;
	memset(&msg, 0, sizeof(ipcmsg_t));

	msg.senderid_t.cid = M4;
	msg.senderid_t.pid = Tarea2;
	msg.opcode = Code2;
	msg.operand[0] = (operand_t) ptr;
	msg.operand[1] = nsamples;

	IPC_SendMsg(&ipcsend ,&msg);
}

static void FIR_Filter(float * ptr, uint32_t nsamples)
{
	/*
	 *
	 * Implementación filtro FIR
	 *
	 */
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
	ipcmsg_t msg;
	float * ptr; // puntero a la direccion de memoria donde se encuentra almacenado el array con las muestras
	uint32_t nsamples; // numero de muestras a procesar

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

		while(IPC_MsgWaiting(&ipcreceive))
		{
			memset(&msg, 0, sizeof(ipcmsg_t));

			IPC_Pop(&ipcreceive, &msg);

			ptr = (float *) msg.operand[0];
			nsamples = msg.operand[1];

			FIR_Filter(ptr, nsamples);

			SendIPCMsg_ProcessingComplete(ptr, nsamples);
			__SEV();
		}

		/* Enable IRQ for M0 Core */
		NVIC_EnableIRQ(M0APP_IRQn);
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
