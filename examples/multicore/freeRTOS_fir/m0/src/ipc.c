/*
 * FreeRTOS_ipc.c
 *
 *  Created on: 19 de may. de 2017
 *      Author: Martin
 */

/*==================[inclusions]=============================================*/

#include "../../../freeRTOS_fir/m0/inc/ipc.h"

/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal functions definition]=========================*/


/*==================[external functions definition]==========================*/

ipcstatus_t IPC_CreateStatic (ipcrb_t *ipcrb, uint8_t *ipcbuf)
{
	memset(ipcbuf, 0, 512);
	RingBuffer_Init(ipcrb, ipcbuf, sizeof(ipcmsg_t), MAX_MSG);
	return success;
}

ipcstatus_t IPC_SendMsg (ipcrb_t *ipcrb, ipcmsg_t *msg)
{
	if(RingBuffer_Insert(ipcrb, msg)) return success;
	else return error;
}

ipcmsgcount_t IPC_MsgWaiting (ipcrb_t *ipcrb)
{
	return RingBuffer_GetCount(ipcrb);
}

ipcstatus_t IPC_Pop (ipcrb_t *ipcrb, ipcmsg_t *msg)
{
	if (RingBuffer_Pop(ipcrb, msg)) return success;
	else return error;
}

/*==================[interrupt handling]==========================*/




