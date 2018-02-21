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
#include <stdlib.h>

#include "FreeRTOSConfig.h"
#include "ipc.h"
#include "UART_freeRTOS_driver.h"

/*==================[macros and definitions]=================================*/

#define MUESTRAS	60
#define FIELD_SIZE	16

/*==================[internal data declaration]==============================*/

static SemaphoreHandle_t xSemaphoreIRQ;

__attribute__ ((section(".AHB_ETB16"))) static float arraytest[60];

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

static void SendIPCMsg_ArraytestSend(void);

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

	IPC_CreateStatic(&ipcsend, ipcbufsend);
	IPC_CreateStatic(&ipcreceive, ipcbufreceive);

	/* Configures and associates the uC RIT to the freeRTOS tick */
	prvSetupTimerInterrupt();

    /* Enable IRQ for M4 Core */
    NVIC_EnableIRQ(M4_IRQn);

}

static void SendIPCMsg_ArraytestSend(void)
{
	ipcmsg_t msg;
	memset(&msg, 0, sizeof(ipcmsg_t));

	msg.senderid_t.cid = M0;
	msg.senderid_t.pid = Tarea1;
	msg.opcode = Code1;
	msg.operand[0] = (operand_t) arraytest;
	msg.operand[1] = MUESTRAS;

	IPC_SendMsg(&ipcsend ,&msg);
}

static void parser(uint8_t * data, uint32_t bytes)
{
	uint32_t count = 0;
	uint8_t * ptr;
	char * origin;

	origin = (char *) data;

	for(uint32_t i = 0 ; i < bytes ; i++)
	{
		/* Busco el \r\n */
		ptr = data + i;
		if( *ptr == '\r' )
		{
			/* reemplazo el \r por \0 para poder utilizar atof */
			*ptr = '\0';

			/* convierto el numero a float y lo almaceno en un array
			 * origin esta alineado con el principio del dato a convertir */
			arraytest[count] = atof(origin);
			/* muevo origin dos posiciones más adelante que ptr (el cual esta alineado con
			 * el \r para ubicarlo al comienzo del próximo dato */
			origin = ptr + 2;
			/* aumento count para escribir en la siguiente posición del array de destino en la próxima
			 * iteración */
			count++;
		}
	}
}

static void printarray(float * ptr, uint32_t nsamples)
{
	char aux[32];
	uint8_t writearray[1024];
	uint32_t i = 0;
	uint32_t length = 0;
	uint8_t * cpyptr = writearray;

	memset(writearray, 0, sizeof(writearray));

	for(i = 0 ; i < nsamples ; i++)
	{
		memset(aux, 0, sizeof(aux));
		snprintf(aux, sizeof(aux), "%f\r\n" , *(ptr+i));
		length = strlen(aux);
		memcpy(cpyptr, aux, length);
		cpyptr +=length;
	}

	UART_freeRTOS_WriteNBytes(UART2, writearray, strlen(writearray));
}
/*==================[interrupt handling]==========================*/

void MX_CORE_IRQHandler(void)
{
	/* limpiamos el evento seteado por el core remoto */
	LPC_CREG->M4TXEVENT = 0;   /* ACK */

	/* Disable IRQ for M0 Core while it's being handled */
	NVIC_DisableIRQ(M4_IRQn);

	long lHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR( xSemaphoreIRQ, &lHigherPriorityTaskWoken );
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken ); /* depends on the port for the uC being used
	more info -> "http://www.freertos.org/FAQISR.html" */
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

static void UARTPolling(void * a)
{
	uarts_e uart = (uarts_e) a;
	uint32_t count = 0;
	uint8_t array[1024];

	while(1)
	{
		count = UART_freeRTOS_DataCount(uart);
		if(count != 0)
		{
			memset(array, 0, sizeof(array));
			memset(arraytest, 0, sizeof(arraytest));

			UART_freeRTOS_GetNBytes(uart, array, count);
			parser(array, count);

			SendIPCMsg_ArraytestSend();
			__SEV();
		}

		vTaskDelay(500 / portTICK_RATE_MS);
	}
}

static void taskM4IRQHandler(void * a)
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

			printarray(ptr, nsamples);

		}

		/* Enable IRQ for M0 Core */
		NVIC_EnableIRQ(M4_IRQn);
	}
}


/*==================[external functions definition]==========================*/

int main(void)
{
	initHardware();

	UART_freeRTOS_Init(UART2);

	xTaskCreate(
				taskledCIAA, /* nombre de la tarea como se declaró */
			    (const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*2, /* tamaño de la pila en palabras no bytes */
				&t1, /* parámetro que le pasas a la función (void * a) -> comodín */
				tskIDLE_PRIORITY+1, /* prioridad (d2e 1 en adelante) */
				0);

	xTaskCreate(
				UARTPolling, /* nombre de la tarea como se declaró */
				(const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*3, /* tamaño de la pila en palabras no bytes */
				(void *) UART2, /* parámetro que le pasas a la función (void * a) -> comodín */
				tskIDLE_PRIORITY+1, /* prioridad (d2e 1 en adelante) */
				0);

	xTaskCreate(
				taskM4IRQHandler, /* nombre de la tarea como se declaró */
				(const char *)"task", /* string descriptivo opcional */
				configMINIMAL_STACK_SIZE*4, /* tamaño de la pila en palabras no bytes */
				0, /* parámetro que le pasas a la función (void * a) -> comodín */
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
