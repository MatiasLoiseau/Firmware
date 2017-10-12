/* Diagrama de conexion ESP8266
  ?--------------------------------?
  |  |       ?????                 |
  |  ?-?     ?????      RX OO VCC  |
  |  ?-? |           GPIO0 OO RST  |
  |  ?-? |   ?????   GPIO2 OO CH_PD|
  |  ?-? |   ?????     GND OO TX   |
  |  ?---?                         |
  ?--------------------------------?

   VCC ESP8266 <--> +3.3V EDU-CIAA-NXP
   RST ESP8266 <--> (SIN CONEXION)
 CH_PD ESP8266 <--> +3.3V EDU-CIAA-NXP
    TX ESP8266 <--> RX EDU-CIAA-NXP

    RX ESP8266 <--> TX EDU-CIAA-NXP
 GPIO0 ESP8266 <--> (SIN CONEXION)
 GPIO0 ESP8266 <--> (SIN CONEXION)
   GND ESP8266 <--> GND EDU-CIAA-NXP

  AT commands: http://www.pridopia.co.uk/pi-doc/ESP8266ATCommandsSet.pdf
*/

/*==================[inclusions]=============================================*/

#include "programa.h"           /* <= own header */

#include "sapi.h"               /* <= sAPI header */

/*==================[macros and definitions]=================================*/

#define BAUD_RATE 115200 // Baudrate por defecto del ESP8266

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void imprimirMensajeDeBienvenida( void ){

   /* Imprimo el mensaje de bienvenida */
   uartWriteString( UART_USB,
      "Bievenido al asistente de configuracion del modulo ESP8266\r\n" );
   uartWriteString( UART_USB,
      "Antes de continuar, por favor asegurese que su terminal\r\n" );
   uartWriteString( UART_USB,
      "serie dispone del terminador CR+LF (enter)\r\n\r\n" );
   uartWriteString( UART_USB,
      "A continuacion se realiza un listado de algunos de los\r\n" );
   uartWriteString( UART_USB, "comandos AT disponibles:\r\n\r\n" );
   uartWriteString( UART_USB,
      "> Saber si el modulo responde correctamente: AT\r\n" );
   uartWriteString( UART_USB,
      "> Version del Firmware: AT+GMR\r\n" );
   uartWriteString( UART_USB, "> Resetear el modulo: AT+RST\r\n" );
   uartWriteString( UART_USB,
      "> Listar todas las redes disponibles: AT+CWLAP\r\n" );
   uartWriteString( UART_USB,
      "> Checkear la red actual: AT+CWJAP?\r\n" );
   uartWriteString( UART_USB,
      "> Unirse a una red: AT+CWJAP=\"nombreRedInalambrica\",\"password\"\r\n" );
   uartWriteString( UART_USB,
      "  - NOTA: Las comillas dobles son parte del mensaje\r\n" );
   uartWriteString( UART_USB,
      "> Salir de la red: AT+CWQAP\r\n" );

   delay(100);
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar las UART a 115200 baudios */
   uartConfig( UART_USB, BAUD_RATE );
   uartConfig( UART_232, BAUD_RATE );

   uint8_t rxData = 0;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      /* Si presionan TEC1 muestro el mensaje de bienvenida */
      if( !gpioRead( TEC1 ) ){
         gpioWrite( LEDB, ON );
         imprimirMensajeDeBienvenida();
         gpioWrite( LEDB, OFF );
      }

      // Brisge entre UART_USB y UART_232

      // Si recibe un byte de la UART_USB lo guardarlo en la variable rxData.
      if( uartReadByte( UART_USB, &rxData ) ){
         // Se reenvía el dato a la UART_232
         uartWriteByte( UART_232, rxData );
      }

      // Si recibe un byte de la UART_232 lo guardarlo en la variable rxData.
      if( uartReadByte( UART_232, &rxData ) ){
         // Se reenvía el dato a la UART_USB
         uartWriteByte( UART_USB, rxData );
      }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
