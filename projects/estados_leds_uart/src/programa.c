/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

uint8_t receivedByte = 0;
uint8_t ledb = OFF;

delay_t miDelay;


void checkUartUserInput( void );

void printStatus( void );



// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   boardConfig(); // Inicializar y configurar la plataforma

   uartConfig( UART_USB, 115200 ); // Inicializar la UART2 a 115200 baudios

   delayConfig( &miDelay, 1000 );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {

      checkUartUserInput();

      printStatus();

      sleepUntilNextInterrupt();

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}


void printStatus( void ){

   // Si se cumple el delay, entonces ejecutar
   if( delayRead( &miDelay ) ){

      // Mostrar estado de leds en Terminal Serie

      if( gpioRead(LEDR) ){
         uartWriteString( UART_USB, "LEDR ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LEDR OFF.\r\n" );
      }
      if( gpioRead(LEDG) ){
         uartWriteString( UART_USB, "LEDG ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LEDG OFF.\r\n" );
      }
      if(ledb){
         uartWriteString( UART_USB, "LEDB ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LEDB OFF.\r\n" );
      }
      if( gpioRead(LED1) ){
         uartWriteString( UART_USB, "LED1 ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LED1 OFF.\r\n" );
      }
      if( gpioRead(LED2) ){
         uartWriteString( UART_USB, "LED2 ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LED2 OFF.\r\n" );
      }
      if( gpioRead(LED3) ){
         uartWriteString( UART_USB, "LED3 ON.\r\n" );
      } else{
         uartWriteString( UART_USB, "LED3 OFF.\r\n" );
      }


      // Mostrar estado de teclas en Terminal Serie

      uint8_t i=0;

      for( i=0; i<4; i++ ){

         uartWriteString( UART_USB, "TEC" );
         uartWriteByte( UART_USB, i+49 );

         if( !(gpioRead(TEC1+i)) ){
            uartWriteString( UART_USB, " PUSH.\r\n" );
         } else{
            uartWriteString( UART_USB, " RELEASED.\r\n" );
         }
      }

      uartWriteString( UART_USB, "\r\n" );

   }

   //delay( 1000 );  // Retardo bloqueante durante 1s
}

void checkUartUserInput( void ){

   // Se Recibe de la UART2 del microcontrolador, si hay byte recibido
   // entonces se chequea que letra es y ejecuta el pedido corresponiente
   if( uartReadByte( UART_USB, &receivedByte ) ){
      switch( receivedByte ){
         case 'a': // Si recibe 'a' intercambia el valor del LEDB
            //gpioToggle( LEDB ); // Intercambia el valor del LEDB

            /*
            if(ledb){ // Intercambia el valor del LEDB
               ledb = 0;
            } else{
               ledb = 1;
            }
            */
            ledb = !ledb; // idem if-else de arriba

            gpioWrite( LEDB, ledb );

         break;
         case 'v': // Si recibe 'v' intercambia el valor del LEDG
            gpioToggle( LEDG ); // Intercambia el valor del LEDG
         break;
         case 'r': // Si recibe 'r' intercambia el valor del LEDR
            gpioToggle( LEDR ); // Intercambia el valor del LEDR
         break;
         case '1': // Si recibe '1' intercambia el valor del LED1
            gpioToggle( LED1 ); // Intercambia el valor del LED1
         break;
         case '2': // Si recibe '2' intercambia el valor del LED2
            gpioToggle( LED2 ); // Intercambia el valor del LED2
         break;
         case '3': // Si recibe '3' intercambia el valor del LED3
            gpioToggle( LED3 ); // Intercambia el valor del LED3
         break;
         default: // Si recibe cualquier otra cosa envia un mensaje de error
            uartWriteString( UART_USB, "Error. Ingrese a, v, r, 1, 2 o 3.\r\n" );
         break;
      }
   }

}



/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
