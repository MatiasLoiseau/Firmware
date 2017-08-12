/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "blinky.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "stdint.h"
#include "teclasMEF.h"
/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/


teclasMEFStruct_t teclasArray[]=
{
    {TEC1,teclaINICIAR_MEF},
    {TEC2,teclaINICIAR_MEF},
    {TEC3,teclaINICIAR_MEF},
    {TEC4,teclaINICIAR_MEF}
};

uint32_t teclasTimePuls[4] = {0, 0, 0, 0};
uint32_t teclasTimePuls_0[4] = {0, 0, 0, 0};

uint8_t teclasTimePulsAscii[4][6]=
{
    {'0','0','0','0','0',0},
    {'0','0','0','0','0',0},
    {'0','0','0','0','0',0},
    {'0','0','0','0','0',0}
};

uint32_t tick_count = 0;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/



// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- CONFIGURACIONES ------------------------------
    // Inicializar y configurar la plataforma
    boardConfig();

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


void ErrorHook( void )
{
    ShutdownOS( 0 );
}

ALARMCALLBACK( CallbackTickCount )
{
	tick_count ++;
}

ALARMCALLBACK( CallbackToggleLed )
{
    gpioToggle( LED3 );
}

TASK( Tarea_A )
{
	const uint8_t i = 0;

	SetRelAlarm( Alamar_Medir_Tecla, 0 , 30 );

	while(1)
	{
		//WaitEvent( evento_muestreo_tecla );
		//ClearEvent( evento_muestreo_tecla );


		/* MAQUINA DE ESTADOS DE TECLA */
		teclasMEFUpdate ( &teclasArray[i] );

		if ( teclasArray[i].teclaEstadoMEF == teclaDOWN )
		{
			 //teclasTimePuls[i] += ( seos_Pont_tasks[handler_task1].Period * seos_Pont_TICKRATEMS );
		}

		if ( teclasArray[i].teclaEstadoMEF == teclaJUST_DOWN )
		{
			//teclasTimePuls[i] = 0;
			teclasTimePuls_0[i] = tick_count;
		}

		if ( teclasArray[i].teclaEstadoMEF == teclaJUST_UP )
		{
			teclasTimePuls[i] = tick_count - teclasTimePuls_0[i];

			/* realizar algun mecanismo para activar tarea_c*/
			ActivateTask( Tarea_C );
		}
	}

	// terminate task
    TerminateTask();
}

TASK( Tarea_C )
{
    const uint8_t i = 0;

    /* ENVIAR POR UART */
    teclasTimePulsAscii[i][4] = (   teclasTimePuls[i] % 10 ) + '0';               //LessSignificDigit
    teclasTimePulsAscii[i][3] = ( ( teclasTimePuls[i] % 100 ) / 10 ) + '0';
    teclasTimePulsAscii[i][2] = ( ( teclasTimePuls[i] % 1000 ) / 100 ) + '0';
    teclasTimePulsAscii[i][1] = ( ( teclasTimePuls[i] % 10000 ) / 1000 ) + '0';
    teclasTimePulsAscii[i][0] = ( ( teclasTimePuls[i] % 100000 ) / 10000 ) + '0'; //MostSignificDigit

    uartWriteString( UART_USB, "Tecla " );
    uartWriteByte( UART_USB, i+1+48 ); /* Envia indice +1*/
    uartWriteString( UART_USB, ": " );
    uartWriteString( UART_USB,( char* ) &( teclasTimePulsAscii[i] ) );
    uartWriteString( UART_USB, "\r\n" );

    // terminate task
    TerminateTask();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
