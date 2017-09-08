/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "osektools.h"
#include "ledsMEF.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/


TASK (ModoOperativo) {

}
TASK (ModoServicio) {

}
TASK (ModoNoche) {

}

TASK (ReadUART) {

	TerminateTask();
}

ISR( uart_usb ){

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
	trataErrorHook();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
