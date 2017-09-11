/*
 * semaforo.c
 *
 *  Created on: 30/7/2017
 *      Author: Mauricio
 */
#include "sapi.h"         /* <= sAPI header */
#include "rx_MEF.h"
#include "os.h"       // <= freeOSEK

typedef struct
{
    char 	        rxComando;                //comando retornado
    uint32_t        rxParametro;              //parametro del comando retornado
    char            rxFlags;                   //flags de estado retornado
    rxestadosMEF    rxEstadoActual;
    uint8_t         rxNAsciiRecibidos;         //contador de caracteres recibidos
    uint8_t         rxNAscii[rxNAsciiTotal];   //acumula ascii
} rx_t;

/* GLOBAL QUE COMPARTE Tarea_B y ISR(uart_usb)*/
static rx_t rxUSB;

uint8_t rxMEFInit( )
{
	GetResource( AccesoGlobalIRQUart );
	rxUSB.rxEstadoActual = rxEnEspera;
    ReleaseResource( AccesoGlobalIRQUart );
    return 1;
}

uint32_t rxMEFUpdate()
{
    uint8_t rx_byteIn;
    TickType Ticks;
    StatusType ret;
    uint32_t rv = 0;

    ret = GetAlarm( rxTimeOut , &Ticks );

    if ( E_OK == ret )
    {
        CancelAlarm( rxTimeOut );
        SetRelAlarm( rxTimeOut , 1000 , 0 );
    }
    else if( E_OS_NOFUNC == ret )
    {
        SetRelAlarm( rxTimeOut , 1000 , 0 );
    }
    else
    {
    	//puede darse este caso?
    }

    uartReadByte( UART_USB, &rx_byteIn );

    GetResource( AccesoGlobalIRQUart );

    rxUSB.rxFlags = 0;

    switch ( rxUSB.rxEstadoActual )
    {
        case rxEnEspera:

            if ( rx_byteIn=='<' )
            {
                rxUSB.rxEstadoActual = rxRecibiendoX;
                rxUSB.rxComando = 0;
                rxUSB.rxNAsciiRecibidos = 0;
            }
            else
            {
                rxUSB.rxFlags |=  RXMEF_FLAG_FRAMEERROR;
                rxUSB.rxEstadoActual = rxEnEspera;
                rv = 1;
            }
            break;

        case rxRecibiendoX:

            if ( ( rx_byteIn=='P' )||( rx_byteIn=='D' ) )
            {
                rxUSB.rxComando = rx_byteIn;
                rxUSB.rxEstadoActual = rxRecibiendoN;
            }
            else
            {
                rxUSB.rxFlags |=  RXMEF_FLAG_FORMATERROR;
                rxUSB.rxEstadoActual = rxEnEspera;

                CancelAlarm( rxTimeOut );
                rv = 1;
            }
            break;

        case rxRecibiendoN:
            if  ( rx_byteIn >= '0' && rx_byteIn <= '9' )
            {
                rxUSB.rxNAsciiRecibidos++;
                rxUSB.rxNAscii[3]=rxUSB.rxNAscii[2];
                rxUSB.rxNAscii[2]=rxUSB.rxNAscii[1];
                rxUSB.rxNAscii[1]=rxUSB.rxNAscii[0];
                rxUSB.rxNAscii[0]=rx_byteIn;

                if ( rxUSB. rxNAsciiRecibidos == rxNAsciiTotal )
                {
                    rxUSB.rxEstadoActual = rxRecibido;
                }
            }
            else
            {
                rxUSB.rxFlags |=  RXMEF_FLAG_FORMATERROR;
                rxUSB.rxEstadoActual = rxEnEspera;
                CancelAlarm( rxTimeOut );
                rv = 1;
            }
            break;

        case rxRecibido:
            if ( rx_byteIn=='>' )
            {
                rxUSB.rxFlags |=  RXMEF_FLAG_OK;
                rxUSB.rxParametro = ( rxUSB.rxNAscii[0]-48 )+( rxUSB. rxNAscii[1]-48 )*10+( rxUSB.rxNAscii[2]-48 )*100+( rxUSB.rxNAscii[3]-48 )*1000;
                rxUSB.rxEstadoActual = rxEnEspera;
                CancelAlarm( rxTimeOut );
            }
            else
            {
                rxUSB.rxFlags |=  RXMEF_FLAG_FRAMEERROR;
                rxUSB.rxEstadoActual = rxEnEspera;
                CancelAlarm( rxTimeOut );
            }

            rv =  1;
            break;

        default:

            rxUSB.rxEstadoActual = rxEnEspera;

            break;
    }

    ReleaseResource( AccesoGlobalIRQUart );

    return rv;
}

/*
 * Obtiene la informacion del paquete recibido
 *
 * Si retorna RXMEF_FLAG_OK los valores de pComando y pParametro
 * son válidos.
 *
 *  Si retorna RXMEF_FLAG_FRAMEERROR o RXMEF_FLAG_FORMATERROR hubo error
 * */
RXRESULT rxMEF_GetReceivedCommand( char *pComando , uint32_t *pParametro)
{
	RXRESULT rv;

	GetResource( AccesoGlobalIRQUart );

	if ( rxUSB.rxFlags & RXMEF_FLAG_OK )
	{
	   *pParametro = rxUSB.rxParametro;
	   *pComando   = rxUSB.rxComando;

	   rv = RXMEF_FLAG_OK;
	}

	if ( rxUSB.rxFlags & RXMEF_FLAG_FRAMEERROR )
	{
	   rv = RXMEF_FLAG_FRAMEERROR;
	}

	if ( rxUSB.rxFlags & RXMEF_FLAG_FORMATERROR )
	{
	   rv = RXMEF_FLAG_FORMATERROR;
	}

	ReleaseResource( AccesoGlobalIRQUart );

	return rv;
}

