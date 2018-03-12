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
	/* Inicializar UART_USB a 115200 baudios */
	uartConfig( UART_USB, 115200 );
	/* Inicializar AnalogIO */
	adcConfig( ADC_ENABLE ); /* ADC */

	// Variable para almacenar el valor leido del ADC CH1
	uint16_t muestra = 0;
	// Variable de delay no bloqueante
	delay_t delayMuestreo;
	// Inicializar Retardo no bloqueante con tiempo en ms
	delayConfig( &delayMuestreo, 0);

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		// delayRead retorna TRUE cuando se cumple el tiempo de retardo
		if ( delayRead( &delayMuestreo ) ){
			// Leo la Entrada Analogica AI0 - ADC0 CH1
			muestra = adcRead( CH1 );
			// Enviar muestra
			uartWriteByte( UART_USB, muestra );
		}
		uartWriteByte( UART_USB, 0 );
	}
	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	  por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
