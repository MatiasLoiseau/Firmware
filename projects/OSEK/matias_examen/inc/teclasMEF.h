/*
 * teclasMEF.h
 *
 *  Created on: 4 sep. 2017
 *      Author: matias
 */

#ifndef PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_
#define PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_

typedef enum {
	esperando,
	recibiendoX,
	recibiendoY,
	completado,
	error
} estadosMEF;

typedef struct{
	uint8_t 	activateAlarmTickCount;	//1 yes, 0 no
	uint8_t		flagSOF;
	uint8_t 	Byte;
	estadosMEF	estadoPaquete;
	uint8_t		paqueteTipoQ;
	uint8_t		paqueteTipoR;
	uint8_t		paqueteTipoS;
	uint8_t		paqueteTipoE;
} paquete;

void datoMEFUpdate ( paquete * );


#endif /* PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_ */
