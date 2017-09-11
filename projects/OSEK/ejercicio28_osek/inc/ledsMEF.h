/*
 * teclasMEF.h
 *
 *  Created on: 4 sep. 2017
 *      Author: matias
 */

#ifndef _LEDSMEF_H_
#define _LEDSMEF_H_

#include "sapi.h"

typedef enum
{
    teclaINICIAR_MEF,
    teclaUP,
    teclaJUST_UP,
    teclaFALLING,
    teclaDOWN,
    teclaJUST_DOWN,
    teclaRISING
} estadosTeclas_t;

typedef struct
{
    gpioMap_t       teclaIO;
    estadosTeclas_t teclaEstadoMEF;
} teclasMEFStruct_t;

void teclasMEFUpdate ( teclasMEFStruct_t * );


#endif /* _LEDSMEF_H_ */
