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

void datoMEFUpdate ( paquete * dato ){

	estadosMEF estadoActual = dato->estadoPaquete;

    switch ( estadoActual ){
        case esperando:
            if (dato->Byte=='<'){
                estadoActual = recibiendoX;
                dato->flagSOF=1;;
                dato->estadoPaquete = recibiendoX;
            }
            else{
            	estadoActual = error;
            	dato->estadoPaquete = error;
            }
            break;

        case recibiendoX:
            if (((dato->Byte=='Q')||(dato->Byte=='S')||(dato->Byte=='R')||(dato->Byte=='E')) && dato->flagSOF == 1){
                estadoActual = recibiendoY;
                dato->estadoPaquete = recibiendoY;
                if(dato->Byte=='Q'){
                	dato->paqueteTipoQ = 1;
                }
                if(dato->Byte=='S'){
                	dato->paqueteTipoS = 1;
                }
                if(dato->Byte=='R'){
                	dato->paqueteTipoR = 1;
                }
                if(dato->Byte=='E'){
                	dato->paqueteTipoE = 1;
                }
            }
            else{
            	estadoActual = error;
            	dato->estadoPaquete = error;
            }
            break;

        case recibiendoY:
        	if(dato->Byte=='>'){
        		estadoActual = completado;
        	}
        	break;

        case completado:
			dato->estadoPaquete = completado;
			estadoActual = esperando;
            break;

        case error:
			dato->estadoPaquete = error;
			dato->flagSOF = 0;
            break;

        default:
            estadoActual = esperando;
            break;
    }

}
