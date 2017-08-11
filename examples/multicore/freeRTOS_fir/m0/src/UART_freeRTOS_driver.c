/* Copyright 2016, Martin Fernandez
 * All rights reserved.
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

/*==================[inclusions]=============================================*/

#include "../../../freeRTOS_fir/m0/inc/UART_freeRTOS_driver.h"

/*==================[macros and definitions]=================================*/

/* -------------- USART0 Port definition and configuration -------------- */

#define U0_TXD_PORT   9
#define U0_TXD_PIN    5
#define U0_TXD_FUNC   (SCU_MODE_INACT | SCU_MODE_FUNC7) /* [UM:Table 190] */

#define U0_RXD_PORT   9
#define U0_RXD_PIN    6
#define U0_RXD_FUNC   (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC7)

#define U0_BAUD_RATE  115200
#define U0_FIFO_CONF  (UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)

#define U0_SETUP      (UART_LCR_WLEN8 | UART_LCR_PARITY_DIS | UART_LCR_SBS_1BIT)


/* -------------- USART2 Port definition and configuration -------------- */

/* -------- Para el proyecto ---------- */
//#define U2_TXD_PORT   2
//#define U2_TXD_PIN    10

/* -------- CIAA USB UART ---------- */
#define U2_TXD_PORT   7
#define U2_TXD_PIN    1
#define U2_TXD_FUNC   (SCU_MODE_INACT | SCU_MODE_FUNC6)  /* [UM:Table 190] */

/* -------- Para el proyecto ---------- */
//#define U2_RXD_PORT   2
//#define U2_RXD_PIN    11

/* -------- CIAA USB UART ---------- */
#define U2_RXD_PORT   7
#define U2_RXD_PIN    2
#define U2_RXD_FUNC   (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC6)

#define U2_BAUD_RATE  115200
#define U2_FIFO_CONF  (UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV3)

#define U2_SETUP      (UART_LCR_WLEN8 | UART_LCR_PARITY_DIS | UART_LCR_SBS_1BIT) /* NMEA Standard:
																						8-bit word length
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 		Parity disabled
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 		1 stop bit */

/* -------------- USART3 Port definition and configuration -------------- */

#define U3_TXD_PORT   2
#define U3_TXD_PIN    3
#define U3_TXD_FUNC   (SCU_MODE_INACT | SCU_MODE_FUNC6)  /* [UM:Table 190] */

#define U3_RXD_PORT   2
#define U3_RXD_PIN    4
#define U3_RXD_FUNC   (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC6)

#define U3_BAUD_RATE  115200
#define U3_FIFO_CONF  (UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)

#define U3_SETUP      (UART_LCR_WLEN8 | UART_LCR_PARITY_DIS | UART_LCR_SBS_1BIT)


/* -------------------- General definitions -------------------- */

#define RS485_CONF (UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1)		/* [UM:40.6.16] */

/* ---------------------- Size definitions ---------------------- */

#define FREERTOS_BUF_SIZE	1024

/*==================[internal data declaration]==============================*/

static QueueHandle_t xQueueRx[3];
static QueueHandle_t xQueueTx[3];
static SemaphoreHandle_t xSemaphoreIRQ[3];
static SemaphoreHandle_t xSemaphoreRx[3];
static SemaphoreHandle_t xSemaphoreTx[3];
static LPC_USART_T * uart[3] = { LPC_USART0, LPC_USART2, LPC_USART3 };

/*==================[internal functions declaration]=========================*/

int32_t UART_Init(uarts_e );
void UART_DeInit(uarts_e );

void UART_freeRTOS_TXIntHandler(uarts_e );
int32_t UART_freeRTOS_RXIntHandler(uarts_e );

int32_t UART_freeRTOS_SendQueue(uarts_e , uint8_t * , uint32_t );
uint32_t UART_freeRTOS_ReadQueue(uarts_e , uint8_t * , uint32_t );

void uart_freeRTOS_irq(uarts_e );

/*==================[internal functions definition]=========================*/

int32_t UART_Init(uarts_e n)
{
	int32_t success = 0, error = -1;

	switch(n)
	{
		case UART0:
			{
				/* USART0 configuration */

				// Set Rx and Tx pin modes and functions
				Chip_SCU_PinMuxSet(U0_TXD_PORT, U0_TXD_PIN, U0_TXD_FUNC); /* [UM:17.4.1] */
				Chip_SCU_PinMuxSet(U0_RXD_PORT, U0_RXD_PIN, U0_RXD_FUNC);

				// USART0 peripheral configuration
				Chip_UART_Init(LPC_USART0);
				Chip_UART_SetBaud(LPC_USART0, U0_BAUD_RATE); /* [UM:40.6.3] [UM:40.6.12] */
				Chip_UART_SetupFIFOS(LPC_USART0, U0_FIFO_CONF); /* [UM:40.6.6] */
				Chip_UART_ConfigData(LPC_USART0, U0_SETUP); /* [UM:40.6.7] */
				Chip_UART_TXEnable(LPC_USART0); /* [UM:40.6.20] */

				// USART0 RS485 configuration
				//Chip_UART_SetRS485Flags(LPC_USART0, RS485_CONF); /* [UM:40.6.16] */

				// Enable USART0 RBR and THRE interrupt
				Chip_UART_IntEnable(LPC_USART0, (UART_IER_RBRINT | UART_IER_THREINT)); /* [UM:40.6.4] */

				// Enable USART0 interrupt in the NVIC. Should be off if DMA mode is being used
				NVIC_ClearPendingIRQ(USART0_IRQn); /* [UM:9.7] */
				NVIC_EnableIRQ(USART0_IRQn);

				return success;
			}

		case UART2:
			{
				/* USART2 configuration */

				// Set Rx and Tx pin modes and functions
				Chip_SCU_PinMuxSet(U2_TXD_PORT, U2_TXD_PIN, U2_TXD_FUNC); /* [UM:17.4.1] */
				Chip_SCU_PinMuxSet(U2_RXD_PORT, U2_RXD_PIN, U2_RXD_FUNC);

				// USART2 peripheral configuration
				Chip_UART_Init(LPC_USART2);
				Chip_UART_SetBaud(LPC_USART2, U2_BAUD_RATE); /* [UM:40.6.3] [UM:40.6.12] */
				Chip_UART_SetupFIFOS(LPC_USART2, U2_FIFO_CONF); /* [UM:40.6.6] */
				Chip_UART_ConfigData(LPC_USART2, U2_SETUP); /* [UM:40.6.7] */
				Chip_UART_TXEnable(LPC_USART2); /* [UM:40.6.20] */

				// USART2 RS485 configuration
				//Chip_UART_SetRS485Flags(LPC_USART2, RS485_CONF); /* [UM:40.6.16] */

				// Enable USART2 RBR and THRE interrupt
				Chip_UART_IntEnable(LPC_USART2, (UART_IER_RBRINT | UART_IER_THREINT)); /* [UM:40.6.4] */

				// Enable USART2 interrupt in the NVIC. Should be off if DMA mode is being used
				NVIC_ClearPendingIRQ(USART2_IRQn); /* [UM:9.7] */
				NVIC_EnableIRQ(USART2_IRQn);

				return success;
			}

		case UART3:
			{
				/* USART3 configuration */

				// Set Rx and Tx pin modes and functions
				Chip_SCU_PinMuxSet(U3_TXD_PORT, U3_TXD_PIN, U3_TXD_FUNC); /* [UM:17.4.1] */
				Chip_SCU_PinMuxSet(U3_RXD_PORT, U3_RXD_PIN, U3_RXD_FUNC);

				// USART2 peripheral configuration
				Chip_UART_Init(LPC_USART3);
				Chip_UART_SetBaud(LPC_USART3, U3_BAUD_RATE); /* [UM:40.6.3] [UM:40.6.12] */
				Chip_UART_SetupFIFOS(LPC_USART3, U3_FIFO_CONF); /* [UM:40.6.6] */
				Chip_UART_ConfigData(LPC_USART3, U3_SETUP); /* [UM:40.6.7] */
				Chip_UART_TXEnable(LPC_USART3); /* [UM:40.6.20] */

				// USART3 RS485 configuration
				//Chip_UART_SetRS485Flags(LPC_USART3, RS485_CONF); /* [UM:40.6.16] */

				// Enable USART2 RBR and THRE interrupt
				Chip_UART_IntEnable(LPC_USART3, (UART_IER_RBRINT | UART_IER_THREINT)); /* [UM:40.6.4] */

				// Enable USART2 interrupt in the NVIC. Should be off if DMA mode is being used
				NVIC_ClearPendingIRQ(USART3_IRQn); /* [UM:9.7] */
				NVIC_EnableIRQ(USART3_IRQn);

				return success;
			}

		default:	return error;
	}
}

void UART_DeInit(uarts_e n)
{
	Chip_UART_DeInit(uart[n]);
}

/* These functions were adapted from the LPCOpen libraries to work with FreeRTOS; they operate in the same way */

/* TODO: fix condition on Chip_UART_ReadlineStatus to actually fill the Tx FIFO (bug LPCOpen)
 * 		 As it is right now it only writes one byte into the FIFO before exiting the loop. What we want is to
 * 		 fill the TX FIFO so we interrupt fewer times per transmit*/
void UART_freeRTOS_TXIntHandler(uarts_e n)
{
	uint8_t ch;

	/* Fill FIFO until full or until TX queue is empty */
	while ((Chip_UART_ReadLineStatus(uart[n]) & UART_LSR_THRE) != 0 &&
			xQueueReceive(xQueueTx[n], (void *) &ch, (TickType_t) 0))
	{
		Chip_UART_SendByte(uart[n], ch);
	}

	/* Disable transmit interrupt if the queue is empty */
	if (uxQueueMessagesWaiting(xQueueTx[n]) == 0) {
		Chip_UART_IntDisable(uart[n], UART_IER_THREINT);
	}
	else
	{
		/* Enable UART transmit interrupt */
		Chip_UART_IntEnable(uart[n], UART_IER_THREINT);
	}

}

int32_t UART_freeRTOS_RXIntHandler(uarts_e n)
{
	int32_t success = 0, error = -1;
	uint8_t ch;
	BaseType_t xReturned;

	while (Chip_UART_ReadLineStatus(uart[n]) & UART_LSR_RDR)
	{
		ch = Chip_UART_ReadByte(uart[n]);
		xReturned = xQueueSendToBack(xQueueRx[n], (void *) &ch, (TickType_t) 0);
		if(xReturned != pdTRUE)
		{
			return error; /* Queue is full */
		}
	}

	return success;

}

/* Populate a transmit queue and start UART transmit */
int32_t UART_freeRTOS_SendQueue(uarts_e n, uint8_t *data, uint32_t bytes)
{
	BaseType_t xReturned;
	int32_t success = 0, error = -1;
	uint32_t i;


	xSemaphoreTake(xSemaphoreTx[n], portMAX_DELAY);

	/* Don't let UART transmit ring buffer change in the UART IRQ handler */
	Chip_UART_IntDisable(uart[n], UART_IER_THREINT);

	/* Move as much data as possible into transmit ring buffer */
	for(i = 0 ; i < bytes ; i++)
	{
		xReturned = xQueueSendToBack(xQueueTx[n], (void *) &data[i], (TickType_t) 0);
		if(xReturned != pdTRUE)
		{
			xSemaphoreGive(xSemaphoreTx[n]);
			return error; /* Queue is full */
		}
	}

	UART_freeRTOS_TXIntHandler(n);

	xSemaphoreGive(xSemaphoreTx[n]);

	return success;
}

/* Copy data from a receive queue */
uint32_t UART_freeRTOS_ReadQueue(uarts_e n, uint8_t *data, uint32_t bytes)
{
	uint32_t i;

	xSemaphoreTake(xSemaphoreRx[n], ( TickType_t ) 10);

	for(i = 0 ; i < bytes && xQueueReceive(xQueueRx[n], (void *) &data[i], (TickType_t) 0) == pdTRUE ; i++);

	xSemaphoreGive(xSemaphoreRx[n]);

	return i; /* returns the actual number of items that were read from the queue */
}

void UART_freeRTOS_vIRQHandler(void * a) /* freeRTOS task */
{
	uarts_e n = (uarts_e) a;

	xSemaphoreIRQ[n] = xSemaphoreCreateBinary();
	xSemaphoreRx[n] = xSemaphoreCreateMutex();
	xSemaphoreTx[n] = xSemaphoreCreateMutex();

	if( xSemaphoreIRQ[n] == NULL || xSemaphoreRx[n] == NULL || xSemaphoreTx[n] == NULL )
	{
		while(1)
		{
			/* There was insufficient FreeRTOS heap available for the semaphore to
		be created successfully. */
		}
	}

	xQueueRx[n] = xQueueCreate( FREERTOS_BUF_SIZE , sizeof(uint8_t) );
	xQueueTx[n] = xQueueCreate( FREERTOS_BUF_SIZE , sizeof(uint8_t) );

	if( xQueueRx[n] == NULL || xQueueTx[n] == NULL)
	{
		while(1)
		{
			/* Queue was not created and must not be used. */
		}
	}


	while(1)
	{
		xSemaphoreTake( xSemaphoreIRQ[n], portMAX_DELAY ); /* Semaphore blocks indefinitely
		more info -> "http://www.freertos.org/a00122.html" */

		/* Handle transmit interrupt if enabled */


			if ( (Chip_UART_ReadLineStatus(uart[n]) & UART_LSR_THRE) &&
					(uxQueueMessagesWaiting(xQueueTx[n]) != 0) )
			{
					xSemaphoreTake(xSemaphoreTx[n], portMAX_DELAY);
					UART_freeRTOS_TXIntHandler(n);
					xSemaphoreGive(xSemaphoreTx[n]);
			}

		/* Handle receive interrupt */
		xSemaphoreTake(xSemaphoreRx[n], portMAX_DELAY);
		UART_freeRTOS_RXIntHandler(n); /* extracts data from fifo and copies it into a queue */
		xSemaphoreGive(xSemaphoreRx[n]);

		Chip_UART_IntEnable(uart[n], UART_IER_RBRINT);
	}
}

/*==================[external functions definition]==========================*/

void UART_BaudsConfig(uarts_e n, uint32_t bauds)
{
	Chip_UART_SetBaud(uart[n], bauds); /* [UM:40.6.3] [UM:40.6.12] */
}

void UART_RS485Enable(uarts_e n)
{
	Chip_UART_SetRS485Flags(uart[n], RS485_CONF); /* [UM:40.6.16] */
}

int32_t UART_freeRTOS_Init(uarts_e n)
{
	int32_t success = 0, error = -1;
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	if (UART_Init(n) != success)
	{
		return error;
	}

	xReturned = 	xTaskCreate(
	    							UART_freeRTOS_vIRQHandler, /* nombre de la tarea como se declaró */
									(const char *)"UARTn IRQ Handler", /* string descriptivo opcional */
									512, /* tamaño de la pila */
									(void *) n, /* le paso como parámetro la UART que inicializo | (void * a) -> comodín */
									3, /* prioridad (d2e 1 en adelante) */
									xHandle		/* puntero opcional al handle de la tarea creada. NULL -> no lo uso */);

	if( xReturned != pdPASS )
		{
			return error; /* task wasn't created */
		}

	return success;
}

void UART_freeRTOS_Deinit(uarts_e n)
{
	// fix me
}

uint32_t UART_freeRTOS_DataCount(uarts_e n)
{
	uint32_t nbytes = (uint32_t) uxQueueMessagesWaiting(xQueueRx[n]);

	return nbytes;
}

uint32_t UART_freeRTOS_GetData(uarts_e n, uint8_t *buffer)
{
	uint32_t nbytes, retval;
	nbytes = (uint32_t) uxQueueMessagesWaiting(xQueueRx[n]);
	retval = UART_freeRTOS_ReadQueue(n, buffer, nbytes);

	return retval;
}

uint32_t UART_freeRTOS_GetNBytes(uarts_e n, uint8_t *buffer, uint32_t nbytes)
{
	uint32_t retval;
	retval = UART_freeRTOS_ReadQueue(n, buffer, nbytes);

	return retval;
}

int32_t UART_freeRTOS_WriteNBytes(uarts_e n, uint8_t *buffer, uint32_t nbytes)
{
	int32_t retval;
	retval = UART_freeRTOS_SendQueue(n, buffer, nbytes);

	return retval;
}

/*======================[interrupt handling]==========================*/

void UART0_IRQHandler(void)
{
	Chip_UART_IntDisable(LPC_USART0, UART_IER_THREINT | UART_IER_RBRINT);
	uart_freeRTOS_irq(UART0);
}

void UART2_IRQHandler(void)
{
	Chip_UART_IntDisable(LPC_USART2, UART_IER_THREINT | UART_IER_RBRINT);
	uart_freeRTOS_irq(UART2);
}

void UART3_IRQHandler(void)
{
	Chip_UART_IntDisable(LPC_USART3, UART_IER_THREINT | UART_IER_RBRINT);
	uart_freeRTOS_irq(UART3);
}

void uart_freeRTOS_irq(uarts_e n)
{
	long lHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR(xSemaphoreIRQ[n], &lHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken ); /* depends on the port for the uC being used
	more info -> "http://www.freertos.org/FAQISR.html" */
}
