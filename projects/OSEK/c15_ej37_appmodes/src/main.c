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
#include "teclasMEF.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
/* GLOBAL QUE COMPARTE Tarea_A y Tarea_B*/
uint32_t Periodo = 1000;
uint32_t DC		 = 500;

teclasMEFStruct_t teclasArray[]=
{
    {TEC1,teclaINICIAR_MEF},
    {TEC2,teclaINICIAR_MEF},
    {TEC3,teclaINICIAR_MEF},
    {TEC4,teclaINICIAR_MEF}
};

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
	boardConfig();

	if( !gpioRead(TEC1) )
	{
		 StartOS( AppModeA );
	}
	else
	{
		 /**/
		 StartOS( AppModeB );
	}

    return 0;
}

void StartupHook( void )
{
	if( GetActiveApplicationMode() == AppModeA )
	{
		uartConfig( UART_USB, 57600 );

		Chip_UART_IntEnable( LPC_USART2, UART_IER_RBRINT );  //Receiver Buffer Register Interrupt
		Chip_UART_IntEnable( LPC_USART2, UART_IER_RLSINT ); //LPC43xx User manual page 1118

		rxMEFInit( );

		uartWriteString( UART_USB, "........Inicia OSEK........\r\n" );
	}
}

void ErrorHook( void )
{
    trataErrorHook();
}

TASK( Tarea_LED )
{
	gpioToggle(LED3);
	TerminateTask();
}

TASK(Tarea_ReporteActividad)
{
	uartWriteString( UART_USB, "*\r\n" );    //mando un *
	TerminateTask();
}

TASK( Tarea_Teclas )
{
    const uint8_t i = 0;

    /* MAQUINA DE ESTADOS DE TECLA */
    if( GetActiveApplicationMode() == AppModeB )
    {
    	teclasMEFUpdate ( &teclasArray[0] );
    	teclasMEFUpdate ( &teclasArray[1] );

    	if ( teclasArray[0].teclaEstadoMEF == teclaJUST_DOWN )
    	{
    		 CancelAlarm( Alarma_Tarea_LED );
    		 SetRelAlarm( Alarma_Tarea_LED, 1000 , 1000);
    	}

        if ( teclasArray[1].teclaEstadoMEF == teclaJUST_DOWN )
    	{
    		 CancelAlarm( Alarma_Tarea_LED );
    	     SetRelAlarm( Alarma_Tarea_LED, 2000 , 2000);
    	}
    }

	TerminateTask();
}

/* Llamada desde ISR( uart_usb ) */
TASK( Tarea_AccionProtocolo )
{
	char 	 Comando;
    uint32_t Parametro_;

    RXRESULT rv = rxMEF_GetReceivedCommand( &Comando , &Parametro_ );

    if (rv == RXMEF_FLAG_OK )
    {
        /* Entro seccion critica */

        if( Comando == 'P' )
        {
            Periodo = Parametro_ ;

			CancelAlarm( Alarma_Tarea_LED );
			SetRelAlarm( Alarma_Tarea_LED , Periodo , Periodo );
        }
    }

    if ( rv ==  RXMEF_FLAG_FRAMEERROR )
    {
        gpioWrite( LEDR,ON );
    }

    if ( rv ==  RXMEF_FLAG_FORMATERROR )
    {
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
        ActivateTask( Tarea_AccionProtocolo );
    }
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
