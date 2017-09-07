/*
 * rxMEF.h
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */

#ifndef RX_MEF_H_
#define RX_MEF_H_

#include <stdint.h>

typedef enum { rxEnEspera, rxRecibiendoX, rxRecibiendoN, rxRecibido} rxestadosMEF;

#define  rxNAsciiTotal 4

#define  RXRESULT uint32_t

uint8_t rxMEFInit();
uint32_t rxMEFUpdate();
RXRESULT rxMEF_GetReceivedCommand( char *pComando , uint32_t *pParametro);

#define RXMEF_FLAG_OK			0x01
#define RXMEF_FLAG_ERROR		0x02
#define RXMEF_FLAG_TIMEOUT		0x04
#define RXMEF_FLAG_FRAMEERROR	0x08
#define RXMEF_FLAG_FORMATERROR	0x16

#endif /* RX_MEF_H_ */
