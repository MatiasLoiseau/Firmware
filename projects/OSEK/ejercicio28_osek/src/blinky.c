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

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

TASK (ModoOperativo) {
	TerminateTask();

}
TASK (ModoServicio) {
	TerminateTask();
}
TASK (ModoNoche) {
	TerminateTask();
}

TASK (Blink) {
	gpioToggle(LEDG);
	TerminateTask();
}


uint8_t receivedByte=0;

TASK (ReadUART) {
	if(uartReadByte(UART_USB, &receivedByte)){
		uartWriteString(UART_USB, "HOLANGA\n");
		gpioToggle(LED2);
	}
	uartWriteString(UART_USB, "HOLANGAPORDOS\n");
	gpioToggle(LED2);
	TerminateTask();
}

ISR( uart_usb ){

	ActivateTask(ReadUART);
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
	uartConfig( UART_USB, 57600 );


    //Enable UART Rx Interrupt
    Chip_UART_IntEnable( LPC_USART2, UART_IER_RBRINT );  //Receiver Buffer Register Interrupt

    // Enable UART line status interrupt
    Chip_UART_IntEnable( LPC_USART2, UART_IER_RLSINT ); //LPC43xx User manual page 1118

    //NVIC_SetPriority(USART2_IRQn, 6); //LO HACE EL OSEK A TRAVES DEL OIL

    //Enable Interrupt for UART channel
    //NVIC_EnableIRQ(USART2_IRQn); 	 	//LO HACE EL OSEK A TRAVES DEL OIL


	uartWriteString( UART_USB, "Running exercise 28 OSEK\n");
}

void ErrorHook(void)
{
	uartWriteString( UART_USB, "ERROR HOOK CALLED\n");
	trataErrorHook();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
