/*
 * semaforo.c
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */
#include "sapi.h"         /* <= sAPI header */
#include "rx_MEF.h"

#define TIMESCAN 40

uint8_t rxMEFUpdate( uint8_t * comando, uint8_t * parametro, uint32_t TimeOut )
{
    static rxestadosMEF estadoActual = rxEnEspera;
    static uint8_t rxNAsciiRecibidos=0;
    static uint32_t rxAccTime=0;
    uint8_t rxNAsciiTotal=1;
    uint8_t rx_byteIn;
    uint8_t flags=0;

    if ( estadoActual!=rxEnEspera )
    {
        rxAccTime=rxAccTime+TIMESCAN;
        if ( rxAccTime > TimeOut )
        {
            flags |= FLAG_RX_NOK ;
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
                rxAccTime=0;
                rxNAsciiRecibidos=0;
            }
            break;
        case rxRecibiendoX:
            if ( ( rx_byteIn=='W' )||( rx_byteIn=='R' )||( rx_byteIn=='I' ) )
            {
                *comando=rx_byteIn;
                estadoActual = rxRecibiendoN;
            }
            break;
        case rxRecibiendoN:
            if  ( rx_byteIn >= '0' && rx_byteIn <= '9' )
            {
                rxNAsciiRecibidos++;
                *parametro =rx_byteIn;
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
                flags |= FLAG_RX_OK;
                estadoActual = rxEnEspera;
            }
            break;
        default:
            estadoActual = rxEnEspera;
            break;
    }
    return flags;
}

