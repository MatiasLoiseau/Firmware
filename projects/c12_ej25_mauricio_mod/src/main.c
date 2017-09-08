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

uint32_t Periodo=1000;
uint32_t DC=500;

//bool_t flagOkRx,flagErrorRx;


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
            OsekDelay( AlarmaDC , DC_ );
        }
    }

    if ( ( DC_ != Periodo_ ) )
    {
        gpioWrite( LED3,OFF );
        gpioWrite( LEDR,OFF );
        gpioWrite( LEDG,OFF 																																																														);
    }

    //SetEvent(Tarea_B,  ChangeParams); //evaluar sincronizar tareas con WaitEvent

    TerminateTask();
}

// escanea UART
TASK( Tarea_B )
{
	uint32_t Periodo_;
	tComando parametro;

	uint32_t flags = rxMEFUpdate( &parametro );

    if ( flags & RXMEF_FLAG_OK )
    {
    	/* entro seccion critica */
    	GetResource( AccesoAParametros );

        if( parametro.param_id == 'P' )
        {
            Periodo = parametro.valor ;
        }

        Periodo_ = Periodo;

        if( parametro.param_id == 'D' )
        {
            if ( parametro.valor >= Periodo_ )
		    {
			   DC = Periodo_;   //ajusto Periodo VS DC
		    }
            else
            {
               DC = parametro.valor;
            }
        }

        /* salgo seccion critica */
        ReleaseResource( AccesoAParametros );

        uartWriteString( UART_USB, "ACK\r\n" );    //mando un ack

        gpioWrite( LEDG , ON );

        // WaitEvent(ChangeParams); //evaluar sincronizar tareas con WaitEvent

        CancelAlarm( Alarma_Tarea_A );
        SetRelAlarm( Alarma_Tarea_A , Periodo_ , Periodo_ );

        //flagOkRx=0;
    }

    if ( flags & RXMEF_FLAG_ERROR )
    {
        uartWriteString( UART_USB, "NOACK\r\n" );
        gpioWrite( LEDR,ON );
     //   flagErrorRx=0;
    }

    TerminateTask();
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
