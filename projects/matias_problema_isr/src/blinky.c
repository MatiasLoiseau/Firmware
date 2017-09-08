/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "osektools.h"
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

uint8_t cantVecesBlink;

uint8_t receivedByte;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/


TASK (BlinkLed) {
	gpioToggle(LED1);
	TerminateTask();
}


TASK (ReadUART) {
	CancelAlarm(ActivateBlinkLed);
	gpioToggle(LED3);
	SetRelAlarm(ActivateBlinkLed, 500, receivedByte);
	TerminateTask();
}

ISR( uart_usb )
{
    if(uartReadByte(UART_USB, &receivedByte ))
    {
    	//uartWriteString( UART_USB, "Llego Byte ! !" );
        ActivateTask( ReadUART );
    }
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
    //SetRelAlarm(ActivateBlinkLed, 500, 500);

    uartWriteString( UART_USB, "........Inicia OSEK........\r\n" );
}

void ErrorHook(void)
{
	trataErrorHook();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
