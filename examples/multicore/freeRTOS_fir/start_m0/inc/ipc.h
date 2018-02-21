/*
 * IPC_RingBuffer.h
 *
 *  Created on: 21 de may. de 2017
 *      Author: Martin
 */

#ifndef PROJECTS_M0_INC_FREERTOS_IPC_H_
#define PROJECTS_M0_INC_FREERTOS_IPC_H_

/*==========================[inclusions]=================================*/

#include <board.h>
#include "chip.h"
#include <string.h>
#include "lpc_types.h"
#include "ring_buffer.h"

/*==================[macros and definitions]=================================*/

/* Max n° of messages in ipc queue */
#define MAX_MSG 250

/* -------------------------------------------------------------------------- */

typedef uint32_t coreid_t;
typedef uint32_t processid_t;
typedef uint32_t opcode_t;
typedef uint32_t operand_t;

typedef uint32_t ipcmsgcount_t;

/* -------------------------------------------------------------------------- */

typedef RINGBUFF_T ipcrb_t;

/*=======================[data declaration]===========================*/

/* IPC message structure */
typedef struct{
	struct{
		coreid_t	cid;
		processid_t	pid;
	}senderid_t;
	opcode_t opcode;
	operand_t operand[5];
} ipcmsg_t ;

/* -------------------------------------------------------------------------- */

typedef enum _status
{
	error = 0,
	success = 1
}ipcstatus_t;

typedef enum {
	M4 = 0x100,
	M0 = 0x200
}ipccid_t ;

typedef enum {
	Tarea1 = 0x100,
	Tarea2 = 0x200
}ipcpid_t ;

typedef enum {
	Code1 = 0x100,
	Code2 = 0x200
}ipcopcode_t ;

/*======================[functions declaration]=========================*/

ipcstatus_t IPC_CreateStatic (ipcrb_t *ipcrb, uint8_t *ipcbuf);
ipcstatus_t IPC_SendMsg (ipcrb_t *ipcrb, ipcmsg_t *msg);
ipcmsgcount_t IPC_MsgWaiting (ipcrb_t *ipcrb);
ipcstatus_t IPC_Pop (ipcrb_t *ipcrb, ipcmsg_t *msg);


#endif /* PROJECTS_M0_INC_FREERTOS_IPC_H_ */
