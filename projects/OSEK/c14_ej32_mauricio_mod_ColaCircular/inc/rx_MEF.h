/*
 * semaforo.h
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */

#ifndef RX_MEF_H_
#define RX_MEF_H_

typedef enum { rxEnEspera, rxRecibiendoX, rxRecibiendoN, rxRecibido} rxestadosMEF;

uint8_t rxMEFUpdate( uint8_t *, uint8_t *,uint32_t );

#define FLAG_RX_OK   0x01
#define FLAG_RX_NOK  0x02

#endif /* RX_MEF_H_ */
