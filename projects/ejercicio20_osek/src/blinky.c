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

teclasMEFStruct_t tecla_1 = {TEC1, teclaINICIAR_MEF};
teclasMEFStruct_t tecla_2 = {TEC2, teclaINICIAR_MEF};

uint32_t tickCount = 0;

uint8_t flag_tecla_1 = 0; //No muestra por pantalla si no apreta la TEC1 primero que la TEC2

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



TASK(TickCounter) {
   ++tickCount;
   TerminateTask();
}

TASK(ReadTecs){

	teclasMEFUpdate (&tecla_1);
	teclasMEFUpdate (&tecla_2);

	if(tecla_1.teclaEstadoMEF == teclaJUST_DOWN){
        uartWriteString( UART_USB, "  Timer started by TEC1\n");
		SetRelAlarm(ActivateTickCounter, 0, 50);
		flag_tecla_1 = 1;
	}
	if(tecla_2.teclaEstadoMEF == teclaJUST_DOWN){
		CancelAlarm(ActivateTickCounter);
		uartWriteString( UART_USB, "  Timer ended by TEC2\n");
	}
	if(tecla_2.teclaEstadoMEF == teclaJUST_UP){
		if(flag_tecla_1 == 1){
			uint8_t uartBuff[10];
			tickCount = tickCount * 50;	//Need to pass to MiliSeconds
			itoa( (int) tickCount, (char*)uartBuff, 10 ); /* 10 significa decimal */
			uartWriteString( UART_USB, uartBuff);
			uartWriteString( UART_USB, "  ms");
			tickCount = 0;
			flag_tecla_1 = 0;
		}
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
