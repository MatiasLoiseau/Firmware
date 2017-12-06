/*==================[inclusions]=============================================*/

#include "programa.h"           /* <= own header */
#include "sapi.h"               /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
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

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

	/* ------------- INICIALIZACIONES ------------- */
	/* Inicializar la placa */
	boardConfig();

	uartConfig( UART_USB, 115200 );
	//adcConfig( ADC_ENABLE ); /* ADC --> te setea por default 200k

	/* Buffer to itoa */
	//static char uartBuff[10];

	/* Variable para almacenar el valor leido del ADC CH1 */
	//uint16_t muestra = 0;

	uint8_t dato  = 0;

	delay(1000);

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		uartWriteByte( UART_USB, dato );
		uartWriteByte( UART_USB, "\n" );

		delay(100);
		dato++;
		if(dato==254){
			dato=0;
		}
		/**
		 *
		 if ( delayRead( &delay1 ) ){

         // Leo la Entrada Analogica AI0 - ADC0 CH1
         muestra = adcRead( CH1 );

         // Envío la primer parte del mnesaje a la Uart
         uartWriteString( UART_USB, "ADC CH1 value: " );

         // Conversión de muestra entera a ascii con base decimal
         itoa( muestra, uartBuff, 10 ); /* 10 significa decimal

         // Enviar muestra y Enter
         uartWriteString( UART_USB, uartBuff );
         uartWriteString( UART_USB, ";\r\n" );
		 *
		 *
		 *
		 */
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	  por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
