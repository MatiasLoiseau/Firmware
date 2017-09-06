/*
 * teclasMEF.c
 *
 *  Created on: 28/7/2017
 *      Author: Mauricio
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
                tecla->teclaEstadoMEF=teclaJUSTDOWN;

                //acciones de la transicion
            }
            else
            {
                tecla->teclaEstadoMEF=teclaUP;
            }
            break;

        case teclaJUSTDOWN:
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
                tecla->teclaEstadoMEF=teclaJUSTUP;

                //acciones de la transicion
            }
            else
            {
                tecla->teclaEstadoMEF=teclaDOWN;
            }
            break;

        case teclaJUSTUP:
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
