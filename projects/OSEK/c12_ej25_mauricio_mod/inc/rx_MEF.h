/*
 * semaforo.h
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */

#ifndef RX_MEF_H_
#define RX_MEF_H_

#include <stdint.h>

typedef enum { rxEnEspera, rxRecibiendoX, rxRecibiendoN, rxRecibido} rxestadosMEF;

typedef struct
{
	char 	 param_id;
	uint32_t valor;
} tComando;

uint32_t rxMEFUpdate( tComando* param );


#define RXMEF_FLAG_OK		0x00000001
#define RXMEF_FLAG_ERROR	0x00000002

#endif /* RX_MEF_H_ */
