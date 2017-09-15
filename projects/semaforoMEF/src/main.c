/*============================================================================
 * Autor: Eric Pernia
 * Fecha: 2017-04-03

Ejemplo 1: Semáforo
   Estados:
      - 1-rojo
      - 2-rojo-amarillo
      - 3-verde
      - 4-amarillo
   Cambio de estados por tiempo:
      - Rojo: 2seg
      - Rojo-amarillo: 1seg
      - Verde: 3seg
      - Amarillo: 1seg

 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "../../semaforoMEF/inc/main.h"   // <= su propio archivo de cabecera

#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

// Nuevo tipo de datos enumerado llamado estadoMEF
typedef enum{
   ROJO,          // 0
   ROJO_AMARILLO, // 1
   VERDE,         // 2
   AMARILLO       // 3
} estadoMEF_t;

#define LED_VERDE      LED3
#define LED_AMARILLO   LED2
#define LED_ROJO       LED1

#define SEG_TO_MS(val) ((val)*1000)

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

void prenderRojo( void );
void prenderAmarillo( void );
void prenderVerde( void );
void prenderRojoAmarillo( void );

void romperMEF( void );

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

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
   if( !gpioRead(TEC1) ){
      estadoActual = 58;
   }
}



delay_t tiempoEnRojo;
delay_t tiempoEnRojoAmarillo;
delay_t tiempoEnVerde;
delay_t tiempoEnAmarillo;


// Función Inicializar MEF
void InicializarMEF( void ){
   estadoActual = ROJO;

   delayConfig( &tiempoEnRojo, SEG_TO_MS(2) );
   delayConfig( &tiempoEnRojoAmarillo, SEG_TO_MS(1) );
   delayConfig( &tiempoEnVerde, SEG_TO_MS(3) );
   delayConfig( &tiempoEnAmarillo, SEG_TO_MS(1) );
}

// Función Actualizar MEF
void ActualizarMEF(void){

   switch(estadoActual) {

      case ROJO:
         // Actualizar salida en el estado
         prenderRojo();

         // Chequear si debo cambiar de estado
         // Si se cumplio el tiempo cambiar de estado
         if( delayRead(&tiempoEnRojo) ){
            // Cambiar a otro estado
            estadoActual = ROJO_AMARILLO;
         }
      break;

      case ROJO_AMARILLO:
         // Actualizar salida en el estado
         prenderRojoAmarillo();
         // Chequear si debo cambiar de estado
         // Si se cumplio el tiempo cambiar de estado
         if( delayRead(&tiempoEnRojoAmarillo) ){
            // Cambiar a otro estado
            estadoActual = VERDE;
         }
      break;

      case VERDE:
         // Actualizar salida en el estado
         prenderVerde();
         // Chequear si debo cambiar de estado
         // Si se cumplio el tiempo cambiar de estado
         if( delayRead(&tiempoEnVerde) ){
            // Cambiar a otro estado
            estadoActual = AMARILLO;
         }
      break;

      case AMARILLO:
         // Actualizar salida en el estado
         prenderAmarillo();
         // Chequear si debo cambiar de estado
         // Si se cumplio el tiempo cambiar de estado
         if( delayRead(&tiempoEnAmarillo) ){
            // Cambiar a otro estado
            estadoActual = ROJO;
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

void prenderRojo( void ){
   gpioWrite(LED_ROJO, ON);
   gpioWrite(LED_AMARILLO, OFF);
   gpioWrite(LED_VERDE, OFF);
}

void prenderRojoAmarillo( void ){
   gpioWrite(LED_ROJO, ON);
   gpioWrite(LED_AMARILLO, ON);
   gpioWrite(LED_VERDE, OFF);
}

void prenderAmarillo( void ){
   gpioWrite(LED_ROJO, OFF);
   gpioWrite(LED_AMARILLO, ON);
   gpioWrite(LED_VERDE, OFF);
}

void prenderVerde( void ){
   gpioWrite(LED_ROJO, OFF);
   gpioWrite(LED_AMARILLO, OFF);
   gpioWrite(LED_VERDE, ON);
}

/*==================[fin del archivo]========================================*/
