/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

   gpioConfig( T_COL2, GPIO_INPUT ); // Tiene R de pullup en protoboard

   gpioConfig( T_FIL1, GPIO_INPUT_PULLUP ); // Le configuro una R de pullup interna, entonces no pongo R en el protoboard

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      // Si se presiona el boton conectado a T_FIL1, enciende el LEDR
      gpioWrite( LEDR, !(gpioRead(T_FIL1)) );
      // Si se presiona el boton conectado a T_COL2, enciende el LED3
      gpioWrite( LED3, !(gpioRead(T_COL2)) );

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
