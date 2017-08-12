/*
 * teclasMEF.h
 *
 *  Created on: 28/7/2017
 *      Author: Mauricio
 */

#ifndef TECLASMEF_H_
#define TECLASMEF_H_

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


#endif /* TECLASMEF_H_ */
