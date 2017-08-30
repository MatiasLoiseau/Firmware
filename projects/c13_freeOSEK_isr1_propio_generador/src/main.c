/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "blinky.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK

//0: 1 mismo handler para ambos flancos
//1: handlers diferentes para ambos flancos.
//2: igual que en 1, pero el blink lo hace la isr. En el oil se puede declarar el handler como CAT1
#define GPIO_OPCION		2

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

void StartupHook( void )
{
    boardConfig();

    /* CONFIGURO TERMINAL GPIO2 DE LA EDUCIAA, PIN DEL MICRO P6.5, GPIO3_4*/
    /* extraido de sapi_gpio.c funcion gpioConfig*/
    //Chip_SCU_PinMux( 6, 5, MD_PUP|MD_EZI|MD_ZI,FUNC0 );   /* GPIO3[4]   , INPUT */
    //Chip_GPIO_SetDir( LPC_GPIO_PORT, 3,( 1<<4 ), GPIO_INPUT );	  /* GPIO3[4],   COMO ENTRADA */
    gpioConfig( GPIO2 , GPIO_INPUT);

    /* CONFIGURO ISR (2 HANDLERS PARA EL MISMO PIN) */

    /*Seteo la interrupci�n para el flanco descendente
     *                channel, GPIOx, [y]    <- no es la config del pin, sino el nombre interno de la se�al
     *                      |  |      |
     *                      |  |      |    */
    Chip_SCU_GPIOIntPinSel( 0 , 3,     4 );

    //Borra el pending de la IRQ
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // INT0 (canal 0 -> hanlder GPIO0)

    //Selecciona activo por flanco
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // INT0

    //Selecciona activo por flanco descendente
    Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // INT0

#if GPIO_OPCION==0
    //Selecciona activo por flanco ascendente
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 0 ) ); // INT0
#endif

#if GPIO_OPCION==1 || GPIO_OPCION==2
    /*Seteo la interrupci�n para el flanco descendente
     *                channel, GPIOx, [y]    <- no es la config del pin, sino el nombre interno de la se�al
     *                      |  |      |
     *                      |  |      |    */
    Chip_SCU_GPIOIntPinSel( 1, 3,     4 );

    //Borra el pending de la IRQ
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( 1 ) ); // INT1  (canal 1 -> hanlder GPIO1)

    //Selecciona activo por flanco
    Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( 1 ) ); // INT1

    //Selecciona activo por flanco descendente
    Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( 1 ) ); // INT1


#endif

    //Borra el clear pending de la IRQ y lo activa
       NVIC_ClearPendingIRQ( PIN_INT0_IRQn );
       NVIC_EnableIRQ( PIN_INT0_IRQn );

       NVIC_ClearPendingIRQ( PIN_INT1_IRQn );
       NVIC_EnableIRQ( PIN_INT1_IRQn );


    uartConfig( UART_USB, 115200 );

    uartWriteString( UART_USB, "Buenas!\r\n" );
}

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- CONFIGURACIONES ------------------------------

    // ---------- INICIAR SISTEMA OPERATIVO --------------------
    // Starts the operating system in the Application Mode 1
    // This example has only one Application Mode
    StartOS( AppMode1 );

    // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
    // directamenteno sobre un microcontroladore y no es llamado por ningun
    // Sistema Operativo, como en el caso de un programa para PC.
    return 0;
}


void ErrorHook( void )
{
    uartWriteString( UART_USB, "Maldicion!!\r\n" );
    ShutdownOS( 0 );
}

TASK( PeriodicTask )
{
    // Intercambia el valor del LEDB
    gpioToggle( LED1 );

    uartWriteString( UART_USB, "T1\r\n" );

#if GPIO_OPCION==0
	ActivateTask( PeriodicTask2 );
#endif

#if GPIO_OPCION==1

#endif

    // terminate task
    TerminateTask();
}

TASK( PeriodicTask2 )
{
    // Intercambia el valor del LED3
    gpioToggle( LED3 );

    uartWriteString( UART_USB, "T2\r\n" );

    // terminate task
    TerminateTask();
}

TASK(PeriodicTask3){
	gpioToggle(GPIO5);
	gpioToggle(LED2);
}

ISR( ISR_EXT0 )
{
	/* hago algo */
    ActivateTask( PeriodicTask );

#if GPIO_OPCION==0

#endif

#if GPIO_OPCION==1

#endif

	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 0 ) );
}

ISR( ISR_EXT1 )
{

#if GPIO_OPCION==0

#endif

#if GPIO_OPCION==1
	ActivateTask( PeriodicTask2 );
#endif

#if GPIO_OPCION==2
    gpioToggle( LEDR );
    gpioToggle( LEDG );
    gpioToggle( LEDB );
    gpioToggle( LED1 );
    gpioToggle( LED2 );
    gpioToggle( LED3 );
#endif

	/* hago algo */
    Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT,PININTCH( 1 ) );
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
