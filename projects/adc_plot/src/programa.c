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

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

	/* ------------- INICIALIZACIONES ------------- */
	/* Inicializar la placa */
	boardConfig();
	/* Inicializar UART_USB a 115200 baudios */
	uartConfig( UART_USB, 115200 );
	/* Inicializar AnalogIO */
	adcConfig( ADC_ENABLE ); /* ADC */


	/* Buffer para el cutecom*/
	//static char uartBuff[10];
	// Variable para almacenar el valor leido del ADC CH1
	uint16_t muestra = 0;
	// Variable de delay no bloqueante
	delay_t delayMuestreo;

	// Inicializar Retardo no bloqueante con tiempo en ms
	delayConfig( &delayMuestreo, 100 );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		/* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
		if ( delayRead( &delayMuestreo ) ){

			// Leo la Entrada Analogica AI0 - ADC0 CH1
			muestra = adcRead( CH1 );

			//Conversión de muestra entera a ascii con base decimal
			//El itoa debe descomentarse si se quiere usar el CuteCom y no el SerialPlot
			//itoa( muestra, uartBuff, 10 ); /* 10 significa decimal */

			// Enviar muestra
			if(muestra<256){
				uartWriteByte( UART_USB, muestra );
				//uartWriteString( UART_USB, uartBuff );
			}
			else{
				uartWriteByte( UART_USB, 255);
			}


		}


	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	  por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
