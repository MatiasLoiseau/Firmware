/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "osektools.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

uint8_t cantVecesBlink;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/


TASK (BlinkLed) {
	uartWriteString( UART_USB, "task BlinkLed\n");
	if(cantVecesBlink){
		cantVecesBlink--;
		gpioToggle(LED1);
	}
	TerminateTask();
}


TASK (ReadUART) {
	if(uartReadByte(UART_USB, &cantVecesBlink)){
		CancelAlarm(ActivateBlinkLed);
		SetRelAlarm(ActivateBlinkLed, 500, 1000);
	}
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
	trataErrorHook();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
