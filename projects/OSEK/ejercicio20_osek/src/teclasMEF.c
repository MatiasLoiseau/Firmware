/*
 * teclasMEF.c
 *
 *  Created on: 4 sep. 2017
 *      Author: matias
 */

#include "sapi.h"         /* <= sAPI header */
#include "teclasMEF.h"

/*
 * returns 0: no transition
 *         1: transition
 * */
void teclasMEFUpdate ( teclasMEFStruct_t * tecla )
{
    //MEF debounce de teclas
    uint8_t teclaEstadoActual;

    teclaEstadoActual = gpioRead( tecla->teclaIO );

    switch ( tecla->teclaEstadoMEF )
    {
        case teclaUP:
            if( !teclaEstadoActual )
            {
                tecla->teclaEstadoMEF=teclaFALLING;
            }
            break;

        case teclaFALLING:
            if( !teclaEstadoActual )
            {
                tecla->teclaEstadoMEF=teclaJUST_DOWN;

                //acciones de la transicion
            }
            else
            {
                tecla->teclaEstadoMEF=teclaUP;
            }
            break;

        case teclaJUST_DOWN:
            tecla->teclaEstadoMEF=teclaDOWN;
        //no pongo break;

        case teclaDOWN:
            if( teclaEstadoActual )
            {
                tecla->teclaEstadoMEF=teclaRISING;
            }
            break;

        case teclaRISING:
            if( teclaEstadoActual )
            {
                tecla->teclaEstadoMEF=teclaJUST_UP;

                //acciones de la transicion
            }
            else
            {
                tecla->teclaEstadoMEF=teclaDOWN;
            }
            break;

        case teclaJUST_UP:
            tecla->teclaEstadoMEF=teclaUP;
        //no pongo break;

        case teclaINICIAR_MEF:
            if( teclaEstadoActual )
            {
                tecla->teclaEstadoMEF=teclaUP;
            }
            else
            {
                tecla->teclaEstadoMEF=teclaDOWN;
            }
            break;

        default:
            tecla->teclaEstadoMEF=teclaINICIAR_MEF;
            break;
    }
}
