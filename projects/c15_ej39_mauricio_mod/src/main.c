/*============================================================================
Tarea B: recibe comados de UART XNNNN donde X=D(DutyCycle) o X=P(Periodo) y NNNN=....mseg
Tarea A: Enciende el led con DC y Periodo manejado por tarea A
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "main.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "osektools.h"
#include "rx_MEF.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
/* GLOBAL QUE COMPARTE Tarea_A y Tarea_B*/
uint32_t Periodo = 1000;
uint32_t DC		 = 500;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    StartOS( AppMode1 );
    return 0;
}

void StartupHook( void )
{
    boardConfig();

    uartConfig( UART_USB, 57600 );
    Chip_UART_IntEnable( LPC_USART2, UART_IER_RBRINT );  //Receiver Buffer Register Interrupt
    Chip_UART_IntEnable( LPC_USART2, UART_IER_RLSINT ); //LPC43xx User manual page 1118

    rxMEFInit( );

    uartWriteString( UART_USB, "........Inicia OSEK........\r\n" );
}

void ErrorHook( void )
{
    trataErrorHook();
}

// Periodica blink
TASK( Tarea_A )
{
    uint32_t Periodo_ ;
    uint32_t DC_ ;

    /* entro en seccion critica */
    GetResource( AccesoAParametros );
    Periodo_	= Periodo;
    DC_			= DC;
    ReleaseResource( AccesoAParametros );
    /* salgo de seccion critica */

    if ( ( DC_ > 0 ) )
    {
        gpioWrite( LED3,ON );

        if ( DC_ != Periodo_ )
        {
            OsekDelay( AlarmaDC, DC_ );
        }
    }

    if ( ( DC_ != Periodo_ ) )
    {
        gpioWrite( LED3,OFF );
        gpioWrite( LEDR,OFF );
        gpioWrite( LEDG,OFF );
    }
    TerminateTask();
}

/* Llamada desde ISR( uart_usb ) */
TASK( Tarea_B )
{
	char 	 Comando;
    uint32_t Parametro_;

    RXRESULT rv = rxMEF_GetReceivedCommand( &Comando , &Parametro_ );

    if (rv == RXMEF_FLAG_OK )
    {
        /* Entro seccion critica */
        GetResource( AccesoAParametros );

        if( Comando == 'P' )
        {
            Periodo = Parametro_ ;
        }

        if( Comando == 'D' )
        {
            if ( Parametro_ >= Periodo )
            {
                DC = Periodo;   //ajusto Periodo VS DC
            }
            else
            {
                DC = Parametro_;
            }
        }
        /* salgo seccion critica */

        ReleaseResource( AccesoAParametros );

        uartWriteString( UART_USB, "ACK\r\n" );    //mando un ack
        gpioWrite( LEDG, ON );

        // WaitEvent(ChangeParams); //evaluar sincronizar tareas con WaitEvent

        CancelAlarm( Alarma_Tarea_A );
        SetRelAlarm( Alarma_Tarea_A, Periodo , Periodo );
    }

    if ( rv ==  RXMEF_FLAG_FRAMEERROR )
    {
        uartWriteString( UART_USB, "FRAME ERROR\r\n" );
        gpioWrite( LEDR,ON );
    }

    if ( rv ==  RXMEF_FLAG_FORMATERROR )
    {
        uartWriteString( UART_USB, "FORMAT ERROR\r\n" );
        gpioWrite( LEDR,ON );
    }

    TerminateTask();
}

TASK ( rxTimeOUT )
{
    uartWriteString( UART_USB, "TIMEOUT del puerto USB\r\n" );
    gpioWrite( LEDR , ON );

    rxMEFInit();

    TerminateTask();
}

ISR( uart_usb )
{
    if( rxMEFUpdate() )
    {
        ActivateTask( Tarea_B );
    }
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
