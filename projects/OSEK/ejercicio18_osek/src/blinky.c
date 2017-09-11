/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

uint8_t cantVecesBlink;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/


TASK (BlinkLed) {
	//GetResource( AccesoAParametros );
	if(cantVecesBlink){
		cantVecesBlink--;
		//ReleaseResource( AccesoAParametros );
		gpioToggle(LED1);
	}
	TerminateTask();
}


TASK (ReadUART) {

	 /* entro en seccion critica */
	 //GetResource( AccesoAParametros );
	 uartReadByte(UART_USB, &cantVecesBlink);
		 //ReleaseResource( AccesoAParametros );
		 /* salgo de seccion critica */

	TerminateTask();
}

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

int main( void )
{
   StartOS(AppMode1);
   return 0;
}

void StartupHook(void) {
   boardConfig();
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "Running program...\n");
}

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*
 * void ErrorHook( void )
{
	if( OSErrorGetServiceId() == OSServiceId_GetAlarm && OSErrorGetRet() == E_OS_NOFUNC )
	{

	}
	else
	{
		ShutdownOS( 0 );
	}
}
 *
 */

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
