/*
 * semaforo.c
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */
#include "sapi.h"         /* <= sAPI header */
#include "rx_MEF.h"

#define TIMEOUT 1000
#define TIMESCAN 40

//extern uint8_t comando;
//extern uint32_t parametro;
//extern bool_t flagOkRx,flagErrorRx;

uint32_t rxMEFUpdate( tComando* param )
{
	uint32_t flags = 0;

    static rxestadosMEF estadoActual = rxEnEspera;
    static uint8_t rxNAsciiRecibidos = 0;
    static uint32_t rxAccTime=0;
    static uint8_t rxNAscii[]= {0,0,0,0};

    uint8_t rxNAsciiTotal=4;
    uint8_t rx_byteIn;

    if ( estadoActual != rxEnEspera )
    {
        rxAccTime=rxAccTime+TIMESCAN;

        if ( rxAccTime > TIMEOUT )
        {
        	flags |=  RXMEF_FLAG_ERROR;
            //flagErrorRx = ON;
            estadoActual = rxEnEspera;
        }
    }

    uartReadByte( UART_USB, &rx_byteIn );

    switch ( estadoActual )
    {
        case rxEnEspera:
            if ( rx_byteIn=='<' )
            {
                estadoActual = rxRecibiendoX;
                param->param_id =0;

                rxAccTime=0;
                rxNAsciiRecibidos=0;
            }
            break;

        case rxRecibiendoX:
            if ( ( rx_byteIn=='P' )||( rx_byteIn=='D' ) )
            {
            	param->param_id = rx_byteIn;
                estadoActual = rxRecibiendoN;
            }
            break;

        case rxRecibiendoN:
            if  ( rx_byteIn >= '0' && rx_byteIn <= '9' )
            {
                rxNAsciiRecibidos++;
                rxNAscii[3]=rxNAscii[2];
                rxNAscii[2]=rxNAscii[1];
                rxNAscii[1]=rxNAscii[0];
                rxNAscii[0]=rx_byteIn;
                if ( rxNAsciiRecibidos == rxNAsciiTotal )
                {
                    estadoActual = rxRecibido;
                    rxAccTime=0;
                }
            }
            break;

        case rxRecibido:
            if ( rx_byteIn=='>' )
            {
            	flags |=  RXMEF_FLAG_OK;
              //  flagOkRx = ON;
                param->valor = ( rxNAscii[0]-48 )+( rxNAscii[1]-48 )*10+( rxNAscii[2]-48 )*100+( rxNAscii[3]-48 )*1000;
                estadoActual = rxEnEspera;
            }
            break;

        default:
            estadoActual = rxEnEspera;
            break;
    }

    return flags;
}

