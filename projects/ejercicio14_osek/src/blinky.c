/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

/*==================[definiciones y macros]==================================*/

uint32_t tiempo_conmutacion = 50;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

void UartMonitorInit() {
   uartConfig( UART_USB, 115200 );
   uartWriteString( UART_USB, "ready osek ej14\n");
}

void Led1Init() {
   gpioConfig(LED1, GPIO_OUTPUT);
}

TASK (BlinkLed) {
   gpioToggle(LED1);
   TerminateTask();
}


TASK (ChangeDelay) {
   CancelAlarm(ActivateBlinkLed);
   tiempo_conmutacion += 10;
   SetRelAlarm(ActivateBlinkLed,0,tiempo_conmutacion);
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
   UartMonitorInit();
   Led1Init();
}

void ErrorHook(void)
{
   uartWriteString( UART_USB, "ShutdownOS\n");
   ShutdownOS(0);
}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


/*==================[end of file]============================================*/
