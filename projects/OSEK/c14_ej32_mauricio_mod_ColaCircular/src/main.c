/*============================================================================
 * * saber que tecla se pulsa con IRQ
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "main.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "stdint.h"
#include "osektools.h"
#include "cc.h"
#include "rx_MEF.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
#define TAM 10
uint8_t arregloCola1[TAM];
ccADT8_t cola1;

uint8_t comando;
uint8_t parametro;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/



// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- INICIAR SISTEMA OPERATIVO --------------------
    // Starts the operating system in the Application Mode 1
    // This example has only one Application Mode
    StartOS( AppMode1 );


    // StartOs shall never returns, but to avoid compiler warnings or errors
    // 0 is returned

    // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
    // directamenteno sobre un microcontroladore y no es llamado por ningun
    // Sistema Operativo, como en el caso de un programa para PC.
    return 0;
}

void StartupHook( void )
{
    boardConfig();

    uartConfig( UART_USB, 57600 );
    uartWriteString( UART_USB, "........Inicia OSEK........\r\n" );
    cc8_Config ( &cola1,arregloCola1,TAM );
}


void ErrorHook( void )
{
    trataErrorHook();
}
// escanea UART
TASK( TareaUART )
{
    uint8_t retornoRX;
    uint32_t TimeOut=1000;

    //formato de <CX> donde <> son delimitadores luego comando y 1 parametro
    retornoRX = rxMEFUpdate( &comando,&parametro,TimeOut );

    if ( retornoRX & FLAG_RX_OK )
    {
        if( comando=='R' )
        {
            uartWriteString( UART_USB, "Comando de Lectura a CC\r\n" );
            SetEvent( EventoLee,CCSacaD );
        }
        if( comando=='W' )
        {
            uartWriteString( UART_USB, "Comando de Escritura a CC\r\n" );
            SetEvent( EventoEsc, CCIngresaD );
        }
        if( comando=='I' )
        {
            uartWriteString( UART_USB, "Comando de RESET a CC\r\n" );
            ChainTask( CCInicia );
        }
    }
    if ( retornoRX & FLAG_RX_NOK )
    {
        uartWriteString( UART_USB, "Algo no anda bien en RXTX \r\n" );
    }
    TerminateTask();
}

TASK( CCIngresaD )
{
    WaitEvent( EventoEsc );
    ClearEvent( EventoEsc );

    cc8_Write ( &cola1, &parametro );

    if ( !( cola1.flags &  CC_FLAG_LLENO ) )
    {
        uartWriteString( UART_USB, "El valor ingresado fue:" );
        uartWriteByte( UART_USB, parametro );
        uartWriteString( UART_USB, "\r\n" );

        if ( ( cola1.flags &  CC_FLAG_VACIO ) )
        {
            SetEvent( EventoMasDatos,CCSacaD );
        }
    }
    else
    {
        uartWriteString( UART_USB, "--------SE LLENO CC--------\r\n" );
        WaitEvent( EventoHayLugar );
        ClearEvent( EventoHayLugar );
    }

    ChainTask( CCIngresaD );
}

TASK( CCSacaD )
{
    uint8_t leido = 0;

    WaitEvent( EventoLee );
    ClearEvent( EventoLee );

    cc8_Read( &cola1, &leido );

    if ( !( cola1.flags &  CC_FLAG_VACIO ) )
    {
        uartWriteString( UART_USB, "El valor extraido fue:" );
        uartWriteByte( UART_USB, leido );
        uartWriteString( UART_USB, "\r\n" );
        if ( ( cola1.flags &  CC_FLAG_LLENO ) )
        {
            SetEvent( EventoHayLugar,CCIngresaD );
        }
    }
    else
    {
        uartWriteString( UART_USB, "--------SE VACIO CC\r\n--------" );
        WaitEvent( EventoMasDatos );
        ClearEvent( EventoMasDatos );
    }
    ChainTask( CCSacaD );
}

TASK( CCInicia )
{
    cc8_Config ( &cola1 , arregloCola1 , TAM );

    cola1.EventoEsperarDato    = EventoMasDatos;
	cola1.EventoEsperarEspacio = EventoHayLugar;

    uartWriteString( UART_USB, "--------Reset OK--------\r\n" );    //mando un ack
    TerminateTask( );                    //se termino
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
