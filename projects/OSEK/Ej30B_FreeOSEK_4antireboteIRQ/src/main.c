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

    Chip_GPIOGP_SelectLowLevel(LPC_GPIOGROUP, 0, 0, 1 << 4);  //0, 4  TEC1= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 0, 0, 1 << 4); //0, 4  TEC1= GPIOxport,ypin
    Chip_GPIOGP_SelectHighLevel(LPC_GPIOGROUP, 1, 0, 1 << 4);  //0, 4  TEC1= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 1, 0, 1 << 4); //0, 4  TEC1= GPIOxport,ypin

    Chip_GPIOGP_SelectLowLevel(LPC_GPIOGROUP, 0, 0, 1 << 8);  //0, 8  TEC2= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 0, 0, 1 << 8); //0, 8  TEC2= GPIOxport,ypin
    Chip_GPIOGP_SelectHighLevel(LPC_GPIOGROUP, 1, 0, 1 << 8);  //0, 8  TEC2= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 1, 0, 1 << 8); //0, 8  TEC2= GPIOxport,ypin

    Chip_GPIOGP_SelectLowLevel(LPC_GPIOGROUP, 0, 0, 1 << 9);  //0, 9  TEC3= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 0, 0, 1 << 9); //0, 9  TEC3= GPIOxport,ypin
    Chip_GPIOGP_SelectHighLevel(LPC_GPIOGROUP, 1, 0, 1 << 9);  //0, 9  TEC3= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 1, 0, 1 << 9); //0, 9  TEC3= GPIOxport,ypin

    Chip_GPIOGP_SelectLowLevel(LPC_GPIOGROUP, 0, 1, 1 << 9);  //1, 9  TEC4= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 0, 1, 1 << 9); //1, 9  TEC4= GPIOxport,ypin
    Chip_GPIOGP_SelectHighLevel(LPC_GPIOGROUP, 1, 1, 1 << 9);  //1, 9  TEC4= GPIOxport,ypin
	Chip_GPIOGP_EnableGroupPins(LPC_GPIOGROUP, 1, 1, 1 << 9); //1, 9  TEC4= GPIOxport,ypin

	Chip_GPIOGP_SelectOrMode(LPC_GPIOGROUP, 0);
	Chip_GPIOGP_SelectEdgeMode(LPC_GPIOGROUP, 0);

	Chip_GPIOGP_SelectAndMode(LPC_GPIOGROUP, 1);
	Chip_GPIOGP_SelectEdgeMode(LPC_GPIOGROUP, 1);

	/* Enable Group GPIO interrupt x */
	NVIC_EnableIRQ(GINT0_IRQn);
	NVIC_EnableIRQ(GINT1_IRQn);

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
	NVIC_DisableIRQ(GINT0_IRQn);
	NVIC_DisableIRQ(GINT1_IRQn);
	uint8_t i;
    static uint8_t contador=0;
    contador++;
	for (i = 0; i <= 3; ++i) {
		teclasMEFUpdate ( &teclasArray[i] );
	}
	if (contador==2){
		CancelAlarm(AlarmaTeclado);
		contador=0;
		Chip_GPIOGP_ClearIntStatus(LPC_GPIOGROUP, 0);
		NVIC_EnableIRQ(GINT0_IRQn);
		Chip_GPIOGP_ClearIntStatus(LPC_GPIOGROUP, 1);
		NVIC_EnableIRQ(GINT1_IRQn);
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

ISR( ISR_Tec )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_GPIOGP_ClearIntStatus(LPC_GPIOGROUP, 0);
}

ISR( ISR_TecH )
{
//activo alarma de escaneo
	SetRelAlarm(AlarmaTeclado,0,30);
	Chip_GPIOGP_ClearIntStatus(LPC_GPIOGROUP, 1);
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
