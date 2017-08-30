/*
 * osekdelay.c
 *
 *  Created on: 19/8/2017
 *      Author: franco.bucafusco
 */

#include "os.h"
/*
 * Funcion que retrasa la ejecucion de una tarea "tiempo" ticks.
 * lo hace con UNA alarma one shot POR cada DELAY usado que espera 1 EVENTO para seguir
 *	o SEA : enciendo una alarma para delay y cuya accion sera realizar un SetEvent para seguir.
 *
 * Configurar 3 cosas en el OIL:
 *
   EVENT = EventoDelay;     //1...UNA declaracion del EVENTO

   TASK TareaQueUsaDelay1 {
      ...
      TYPE = EXTENDED;      //2...EN cada Tarea que use delay: sera EXTENDED del EVENTO de delay
      EVENT = EventoDelay;
	  ...
   }

   ALARM AlarmaDelayT1 {    //3...UNA alarma por CADA Tarea que use delay:
      COUNTER = HardwareCounter;
      ACTION = SETEVENT {
         TASK = TareaQueUsaDelay1;
         EVENT = EventoDelay;
      }
   }

//USO dentro de la tarea  TareaQueUsaDelay1

   OsekDelay( AlarmaDelayT1 , tiempo );
 *
 * */
void OsekDelay( AlarmType alarm, TickType tiempo )
{
    /* enciendo una alarma cuya accion sera realizar un SetEvent */
    SetRelAlarm( alarm, tiempo, 0 );
    WaitEvent( EventoDelay );
    ClearEvent( EventoDelay );
}
