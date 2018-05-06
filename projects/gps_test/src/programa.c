/*==================[inclusions]=============================================*/

#include "programa.h"           /* <= own header */
#include "sapi.h"               /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

	/* ------------- INICIALIZACIONES ------------- */
	/* Inicializar la placa */
	boardConfig();

	uartConfig( UART_USB, 115200 );
	uartConfig( UART_232, 9600 );

	uint8_t dataReceivedFromUSBtoGPS  = 0;
	uint8_t dataReceivedFromGPStoUSB  = 0;

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		//if(  uartReadByte( UART_USB, &dataReceivedFromUSBtoGPS ) ){
			//uartWriteByte( UART_232, dataReceivedFromUSBtoGPS );
		//}
		if(  uartReadByte( UART_232, &dataReceivedFromGPStoUSB ) ){
			uartWriteByte( UART_USB, dataReceivedFromGPStoUSB );
		}
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	  por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
