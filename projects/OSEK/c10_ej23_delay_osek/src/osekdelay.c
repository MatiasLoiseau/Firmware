/*
 * osekdelay.c
 *
 *  Created on: 19/8/2017
 *      Author: franco.bucafusco
 */

#include "os.h"
/*
 * Funcion que retrasa la ejecucion de una tarea "tiempo" ticks.
 *
 * Configurar el OIL:
 *
   EVENT = EventoDelay;

   TASK TareaQueUsaDelay1 {
      ...
      TYPE = EXTENDED;
      EVENT = EventoDelay;
	  ...
   }

   ALARM AlarmaDelayT1 {
      ...
      ACTION = SETEVENT {
         TASK = TareaQueUsaDelay1;
         EVENT = EventoDelay;
      }
   }

   uso dentro de la tarea  TareaQueUsaDelay1

   OsekDelay( AlarmaDelayT1 , tiempo );
 *
 * */
void OsekDelay( AlarmType alarm , TickType tiempo )
{
	/* enciendo una alarma cuya accion sera realizar un SetEvent */
	SetRelAlarm( alarm , tiempo , 0 );
	WaitEvent( EventoDelay );
	ClearEvent( EventoDelay );
}
