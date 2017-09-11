/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "osektools.h" // <= trata el ErrorHook y delay
#include "teclasMEF.h" // <= Maquina de Estados de las teclas

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/


uint8_t tickCount = 0;
uint8_t cantPaqueteQ = 0;
uint8_t cantPaqueteR = 0;
uint8_t cantPaqueteS = 0;
uint8_t cantPaqueteE = 0;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

//ITOA
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

void InicializacionTec1ISR() {
   // taken from freertos example
   gpioConfig(TEC1, GPIO_INPUT);
   Chip_SCU_GPIOIntPinSel(0,0,4);
   Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0 );
   Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);
   Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH0);
//   Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH0);
   NVIC_ClearPendingIRQ(PIN_INT0_IRQn);

}

ISR (ISRtec) {
   uartWriteString( UART_USB, "Reiniciando contadores\n");
   cantPaqueteQ = 0;
   cantPaqueteR = 0;
   cantPaqueteS = 0;
   cantPaqueteE = 0;
   Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0 );
}


TASK(BlinkLedRed) {
	gpioToggle(LEDR);
	TerminateTask();
}

TASK(BlinkLedBlue) {
	gpioToggle(LEDB);
	TerminateTask();
}

TASK(TickCounter) {
	++tickCount;
	TerminateTask();
}

paquete dato;	//Es global porque me traía problemas

TASK(ReadUART){
	uint8_t receivedByte;
	if(uartReadByte( UART_USB, &receivedByte)){
		dato.Byte = receivedByte;
		datoMEFUpdate(&dato);
		if(dato.estadoPaquete==completado){
			CancelAlarm(ActivateTickCounter);
            if(dato.Byte=='Q'){
            	cantPaqueteQ++;
            }
            if(dato.Byte=='S'){
            	cantPaqueteS++;
            }
            if(dato.Byte=='R'){
            	cantPaqueteR++;
            }
            if(dato.Byte=='E'){
            	cantPaqueteE++;
            }
			ActivateTask(MostrarUART); //Es necesario porque activo otra vez tickCounter
			SetRelAlarm(ActivateTickCounter, 0, 20);
			CancelAlarm(ActivateBlinkLedRed);
			SetRelAlarm(ActivateBlinkLedBlue, 50, 50);
		}
		if(dato.estadoPaquete==error){
			dato.paqueteTipoQ=0;
			dato.paqueteTipoR=0;
			dato.paqueteTipoS=0;
			dato.paqueteTipoE=0;
			CancelAlarm(ActivateBlinkLedBlue);
			SetRelAlarm(ActivateBlinkLedBlue, 50, 50);
			uartWriteString( UART_USB, "Paquete erroneo\n");
		}
	}
	TerminateTask();
}

TASK(MostrarUART){
	uint8_t uartBuff[10];
	tickCount = tickCount * 20;	//Pasar a milisegundos
	itoa( (int) tickCount, (char*)uartBuff, 10 );
	uartWriteString( UART_USB, (char*)uartBuff);
	uartWriteString( UART_USB, "  ms entre el paquete anterior y el actual\n");
	tickCount = 0;
	/////////////////////////////////////////////////////////////////////////////
	uint8_t uartBuff2[10];
	itoa( (int) cantPaqueteQ, (char*)uartBuff2, 10 );
	uartWriteString( UART_USB, (char*)uartBuff2);
	uartWriteString( UART_USB, "  cant paquetes de tipo Q\n");
	/////////////////////////////////////////////////////////////////////////////
	uint8_t uartBuff3[10];
	itoa( (int) cantPaqueteR, (char*)uartBuff3, 10 );
	uartWriteString( UART_USB, (char*)uartBuff3);
	uartWriteString( UART_USB, "  cant paquetes de tipo R\n");
	/////////////////////////////////////////////////////////////////////////////
	uint8_t uartBuff4[10];
	itoa( (int) cantPaqueteS, (char*)uartBuff4, 10 );
	uartWriteString( UART_USB, (char*)uartBuff4);
	uartWriteString( UART_USB, "  cant paquetes de tipo S\n");
	/////////////////////////////////////////////////////////////////////////////
	uint8_t uartBuff5[10];
	itoa( (int) cantPaqueteE, (char*)uartBuff5, 10 );
	uartWriteString( UART_USB, (char*)uartBuff5);
	uartWriteString( UART_USB, "  cant paquetes de tipo E\n");
	/////////////////////////////////////////////////////////////////////////////
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
	InicializacionTec1ISR();
	uartConfig( UART_USB, 19200 );
	uartWriteString( UART_USB, "Staring OSEK\n");
}

void ErrorHook(void)
{
	trataErrorHook();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[end of file]============================================*/
