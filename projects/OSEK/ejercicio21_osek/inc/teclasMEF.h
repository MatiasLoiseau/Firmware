/*
 * teclasMEF.h
 *
 *  Created on: 4 sep. 2017
 *      Author: matias
 */

#ifndef PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_
#define PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_

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


#endif /* PROJECTS_EJERCICIO20_OSEK_INC_TECLASMEF_H_ */
