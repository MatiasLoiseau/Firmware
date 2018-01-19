/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

// Nuevo tipo de datos enumerado llamado estadoMEF
typedef enum{
   BUTTON_UP,      // Mientras el botón está liberado.
   BUTTON_FALLING, // Mientras esta ocurriendo el flanco descendente, hace el anti-rebote.
   BUTTON_RISING,  // Mientras esta ocurriendo el flanco ascendente, hace el anti-rebote.
   BUTTON_DOWN     // Mientras eNl botón está presionado.
} estadoMEF_t;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[definiciones de datos globales]=========================*/

// Variable de estado (global)
estadoMEF_t estadoActual;

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// Prototipos de funciones
void InicializarMEF( void );
void ActualizarMEF( void );

void romperMEF( void );

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

   uartConfig( UART_USB, 115200 );

   InicializarMEF();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      ActualizarMEF();

      romperMEF();
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

void romperMEF( void ){
   if( !gpioRead(TEC4) ){
      estadoActual = 58;
   }
}


void buttonPressed( void ){
   uartWriteString( UART_USB, "button Pressed\r\n" );
}

void buttonReleased( void ){
   uartWriteString( UART_USB, "button Released\r\n" );
}


// Función Inicializar MEF
void InicializarMEF( void ){
   estadoActual = BUTTON_UP;
}

// Función Actualizar MEF
void ActualizarMEF(void){

   switch(estadoActual) {

      // Si está en estado UP y presionan el pulsador pasa al estado FALLING.
      case BUTTON_UP:      // Mientras el botón está liberado.
         // Actualizar salida en el estado
         // no hace nada...
         // Chequear si debo cambiar de estado
         if( !gpioRead(TEC1) ){
            estadoActual = BUTTON_FALLING;
         }
      break;

      /* Si está en estado FALLING, espera un tiempo de 40 ms y vuelve a leer
         el pulsador, si realmente estaba presionado pasa al estado DOWN y
         llama a la función (evento) buttonPressed(); si no estaba presionado
         vuelve al estado UP. */
      case BUTTON_FALLING: // Mientras esta ocurriendo el flanco descendente, hace el anti-rebote.
         // Actualizar salida en el estado
         delay(40);
         // Chequear si debo cambiar de estado
         if( !gpioRead(TEC1) ){
            estadoActual = BUTTON_DOWN;
            buttonPressed();
         } else{
            estadoActual = BUTTON_UP;
         }
      break;

      /*Si está en estado RISING, espera un tiempo de 40 ms y vuelve a leer
         el pulsador, si realmente estaba liberado pasa al estado UP y llama
         a la función (evento) buttonReleased(); si no estaba liberado vuelve
         al estado DOWN. */
      case BUTTON_RISING:  // Mientras esta ocurriendo el flanco ascendente, hace el anti-rebote.
         // Actualizar salida en el estado
         delay(40);
         // Chequear si debo cambiar de estado
         if( gpioRead(TEC1) ){
            estadoActual = BUTTON_UP;
            buttonReleased();
         } else{
            estadoActual = BUTTON_DOWN;
         }
      break;

      //Si está en estado DOWN y liberan el botón pasa al estado RISING.
      case BUTTON_DOWN:     // Mientras eNl botón está presionado.
         // Actualizar salida en el estado
         // no hace nada...
         // Chequear si debo cambiar de estado
         if( gpioRead(TEC1) ){
            estadoActual = BUTTON_RISING;
         }
      break;

      default:
         //Si algo modificó la variable estadoActual
         // a un estado no válido llevo la MEF a un
         // lugar seguro, por ejemplo, la reinicio:
         InicializarMEF();
      break;

   }
}

/*==================[fin del archivo]========================================*/
