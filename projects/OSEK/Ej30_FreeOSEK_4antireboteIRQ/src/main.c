/*============================================================================
 * * saber que tecla se pulsa con IRQ
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "main.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "stdint.h"
#include "teclasMEF.h"
#include "osektools.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/


teclasMEFStruct_t teclasArray[]=
{
    {TEC1,teclaINICIAR_MEF},
    {TEC2,teclaINICIAR_MEF},
    {TEC3,teclaINICIAR_MEF},
    {TEC4,teclaINICIAR_MEF}
};

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/



// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- INICIAR SISTEMA OPERATIVO --------------------
    // Starts the operating system in the Application Mode 1
    // This example has only one Application Mode
    StartOS( AppMode1 );


    // StartOs shall never returns, but to avoid compiler warnings or errors
    // 0 is returned

    // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
    // directamenteno sobre un microcontroladore y no es llamado por ningun
    // Sistema Operativo, como en el caso de un programa para PC.
    return 0;
}

void StartupHook( void )
{
    boardConfig();

    Chip_SCU_GPIOIntPinSel( 0 , 0,     4 );                        // TEC1= GPIOxport,ypin
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // INT0 (canal 0 -> hanlder GPIO0)
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // MODO
    Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( 0 ) );   // Falling edge
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 0 ) );  // Rising edge
    NVIC_ClearPendingIRQ( PIN_INT0_IRQn );
    NVIC_EnableIRQ( PIN_INT0_IRQn );

    Chip_SCU_GPIOIntPinSel( 1 , 0,     8 );                        // TEC2= GPIOxport,ypin
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 1 ) ); // INT1 (canal 1 -> hanlder GPIO1)
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 1 ) ); // MODO
    Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( 1 ) );   // Falling edge
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 1 ) );  // Rising edge
    NVIC_ClearPendingIRQ( PIN_INT1_IRQn );
    NVIC_EnableIRQ( PIN_INT1_IRQn );

    Chip_SCU_GPIOIntPinSel( 2 , 0,     9 );                        // TEC3= GPIOxport,ypin
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 2 ) ); // INT2 (canal 2 -> hanlder GPIO2)
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 2 ) ); // MODO
    Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( 2 ) );   // Falling edge
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 2 ) );  // Rising edge
    NVIC_ClearPendingIRQ( PIN_INT2_IRQn );
    NVIC_EnableIRQ( PIN_INT2_IRQn );

    Chip_SCU_GPIOIntPinSel( 3 , 1,     9 );                        // TEC4= GPIOxport,ypin
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 3 ) ); // INT0 (canal 3 -> hanlder GPIO3)
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 3 ) ); // MODO
    Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( 3 ) );   // Falling edge
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 3 ) );  // Rising edge
    NVIC_ClearPendingIRQ( PIN_INT3_IRQn );
    NVIC_EnableIRQ( PIN_INT3_IRQn );


    uartConfig( UART_USB, 57600 );
    uartWriteString( UART_USB, "........Inicia OSEK........\r\n" );
}



void ErrorHook( void )
{
trataErrorHook();
}
// escanea tacla
TASK( TareaTeclado )
{
    NVIC_DisableIRQ( PIN_INT0_IRQn );
    NVIC_DisableIRQ( PIN_INT1_IRQn );
    NVIC_DisableIRQ( PIN_INT2_IRQn );
    NVIC_DisableIRQ( PIN_INT3_IRQn );
	uint8_t i;
    static uint8_t contador=0;
    contador++;
	for (i = 0; i <= 3; ++i) {
		teclasMEFUpdate ( &teclasArray[i] );
	}
	if (contador==2){
		CancelAlarm(AlarmaTeclado);
		contador=0;
		Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 0 ) );
	    NVIC_ClearPendingIRQ( PIN_INT0_IRQn );
	    NVIC_EnableIRQ( PIN_INT0_IRQn );
		Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 1 ) );
	    NVIC_ClearPendingIRQ( PIN_INT1_IRQn );
	    NVIC_EnableIRQ( PIN_INT1_IRQn );
		Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 2 ) );
	    NVIC_ClearPendingIRQ( PIN_INT2_IRQn );
	    NVIC_EnableIRQ( PIN_INT2_IRQn );
		Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 3 ) );
	    NVIC_ClearPendingIRQ( PIN_INT3_IRQn );
	    NVIC_EnableIRQ( PIN_INT3_IRQn );
	}
	TerminateTask( );                    //se termino
}

TASK( TareaImprime )
{
	uint8_t i;
	gpioToggle(LED3);
	uartWriteString( UART_USB, "\r\n......................\r\n" );
	for (i = 0; i <= 3; ++i) {
		uartWriteString( UART_USB, "T" );
		uartWriteByte( UART_USB, i+1+48 );
		uartWriteString( UART_USB, ":" );
		if (teclasArray[i].teclaEstadoMEF==teclaDOWN){
			uartWriteString( UART_USB, "ON ;" );
		}
		else{
			uartWriteString( UART_USB, "OFF ;" );
		}

	}

	TerminateTask( );                    //se termino
}

ISR( ISR_Tec1 )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 0 ) );
}
ISR( ISR_Tec2 )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 1 ) );
}
ISR( ISR_Tec3 )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 2 ) );
}
ISR( ISR_Tec4 )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 3 ) );
}
/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
