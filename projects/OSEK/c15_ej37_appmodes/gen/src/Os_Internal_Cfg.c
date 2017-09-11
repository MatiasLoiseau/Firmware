/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Os Generated Internal Configuration Implementation File
 **
 ** \file Os_Internal_Cfg.c
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * JuCe         Juan Cecconi
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150619 v0.1.4 MaCe fix issue #279
 * 20141125 v0.1.3 JuCe additional stack for x86 ARCH
 * 20090719 v0.1.2 MaCe rename file to Os_
 * 20090128 v0.1.1 MaCe add OSEK_MEMMAP check
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
/** \brief Tarea_LED stack */
#if ( x86 == ARCH )
uint8 StackTaskTarea_LED[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskTarea_LED[512];
#endif
/** \brief Tarea_Teclas stack */
#if ( x86 == ARCH )
uint8 StackTaskTarea_Teclas[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskTarea_Teclas[512];
#endif
/** \brief Tarea_ReporteActividad stack */
#if ( x86 == ARCH )
uint8 StackTaskTarea_ReporteActividad[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskTarea_ReporteActividad[512];
#endif
/** \brief Tarea_AccionProtocolo stack */
#if ( x86 == ARCH )
uint8 StackTaskTarea_AccionProtocolo[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskTarea_AccionProtocolo[512];
#endif
/** \brief rxTimeOUT stack */
#if ( x86 == ARCH )
uint8 StackTaskrxTimeOUT[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskrxTimeOUT[512];
#endif

/** \brief Tarea_LED context */
TaskContextType ContextTaskTarea_LED;
/** \brief Tarea_Teclas context */
TaskContextType ContextTaskTarea_Teclas;
/** \brief Tarea_ReporteActividad context */
TaskContextType ContextTaskTarea_ReporteActividad;
/** \brief Tarea_AccionProtocolo context */
TaskContextType ContextTaskTarea_AccionProtocolo;
/** \brief rxTimeOUT context */
TaskContextType ContextTaskrxTimeOUT;

/** \brief Ready List for Priority 1 */
TaskType ReadyList1[3];

/** \brief Ready List for Priority 0 */
TaskType ReadyList0[2];

const AlarmType OSEK_ALARMLIST_HardwareCounter[4] = {
   Alarma_Tarea_LED, /* this alarm has to be incremented with this counter */
   Alarma_Tarea_Teclas, /* this alarm has to be incremented with this counter */
   Alarma_Tarea_ReporteActividad, /* this alarm has to be incremented with this counter */
   rxTimeOut, /* this alarm has to be incremented with this counter */
};


/*==================[external data definition]===============================*/
/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.         Osek P.
 * 2               1
 * 1               0
 */

const TaskConstType TasksConst[TASKS_COUNT] = {
   /* Task Tarea_LED */
   {
       OSEK_TASK_Tarea_LED,   /* task entry point */
       &ContextTaskTarea_LED, /* pointer to task context */
       StackTaskTarea_LED, /* pointer stack memory */
       sizeof(StackTaskTarea_LED), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task Tarea_Teclas */
   {
       OSEK_TASK_Tarea_Teclas,   /* task entry point */
       &ContextTaskTarea_Teclas, /* pointer to task context */
       StackTaskTarea_Teclas, /* pointer stack memory */
       sizeof(StackTaskTarea_Teclas), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task Tarea_ReporteActividad */
   {
       OSEK_TASK_Tarea_ReporteActividad,   /* task entry point */
       &ContextTaskTarea_ReporteActividad, /* pointer to task context */
       StackTaskTarea_ReporteActividad, /* pointer stack memory */
       sizeof(StackTaskTarea_ReporteActividad), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task Tarea_AccionProtocolo */
   {
       OSEK_TASK_Tarea_AccionProtocolo,   /* task entry point */
       &ContextTaskTarea_AccionProtocolo, /* pointer to task context */
       StackTaskTarea_AccionProtocolo, /* pointer stack memory */
       sizeof(StackTaskTarea_AccionProtocolo), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 | ( 1 << AccesoGlobalIRQUart ) ,/* resources mask */
      0 /* core */
   },
   /* Task rxTimeOUT */
   {
       OSEK_TASK_rxTimeOUT,   /* task entry point */
       &ContextTaskrxTimeOUT, /* pointer to task context */
       StackTaskrxTimeOUT, /* pointer stack memory */
       sizeof(StackTaskrxTimeOUT), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   }
};

/** \brief RemoteTaskCore Array */
const TaskCoreType RemoteTasksCore[REMOTE_TASKS_COUNT] = {};

/** \brief TaskVar Array */
TaskVariableType TasksVar[TASKS_COUNT];

/** \brief AutoStart Array */
const AutoStartType AutoStart[2]  = {
   /* Application Mode AppModeA */
   {
      0, /* Total Auto Start Tasks in this Application Mode */
      NULL /* no tasks on this mode */
   },
   /* Application Mode AppModeB */
   {
      0, /* Total Auto Start Tasks in this Application Mode */
      NULL /* no tasks on this mode */
   }
};

const ReadyConstType ReadyConst[2] = { 
   {
      3, /* Length of this ready list */
      ReadyList1 /* Pointer to the Ready List */
   },
   {
      2, /* Length of this ready list */
      ReadyList0 /* Pointer to the Ready List */
   }
};

/** TODO replace next line with: 
 ** ReadyVarType ReadyVar[2] ; */
ReadyVarType ReadyVar[2];

/** \brief Resources Priorities */
const TaskPriorityType ResourcesPriority[2]  = {
   0,
   0
};
/** TODO replace next line with: 
 ** AlarmVarType AlarmsVar[4]; */
AlarmVarType AlarmsVar[4];

const AlarmConstType AlarmsConst[4]  = {
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         Tarea_LED, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         Tarea_Teclas, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         Tarea_ReporteActividad, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         rxTimeOUT, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   }
};

const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {
  {
	  AppModeB, /* Application Mode */
	  Alarma_Tarea_LED, /* Alarms */
	  0, /* Alarm Time */
	  1000 /* Alarm Time */
   },
  {
      AppModeA, /* Application Mode */
      Alarma_Tarea_LED, /* Alarms */
      0, /* Alarm Time */
      1000 /* Alarm Time */
   },
  {
      AppModeB, /* Application Mode */
      Alarma_Tarea_Teclas, /* Alarms */
      0, /* Alarm Time */
      30 /* Alarm Time */
   },
  {
      AppModeA, /* Application Mode */
      Alarma_Tarea_ReporteActividad, /* Alarms */
      0, /* Alarm Time */
      2000 /* Alarm Time */
   }
};

CounterVarType CountersVar[1];

const CounterConstType CountersConst[1] = {
   {
      4, /* quantity of alarms for this counter */
      (AlarmType*)OSEK_ALARMLIST_HardwareCounter, /* alarms list */
      100000, /* max allowed value */
      1, /* min cycle */
      1 /* ticks per base */
   }
};


/** TODO replace the next line with
 ** uint8 ApplicationMode; */
uint8 ApplicationMode;

/** TODO replace the next line with
 ** uint8 ErrorHookRunning; */
uint8 ErrorHookRunning;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void OSEK_ISR2_uart_usb(void)
{
   /* store the calling context in a variable */
   ContextType actualContext = GetCallingContext();
   /* set isr 2 context */
   SetActualContext(CONTEXT_ISR2);

   /* trigger isr 2 */
   OSEK_ISR_uart_usb();

   /* reset context */
   SetActualContext(actualContext);

#if (NON_PREEMPTIVE == OSEK_DISABLE)
   /* check if the actual task is preemptive */
   if ( ( CONTEXT_TASK == actualContext ) &&
        ( TasksConst[GetRunningTask()].ConstFlags.Preemtive ) )
   {
      /* this shall force a call to the scheduler */
      PostIsr2_Arch(isr);
   }
#endif /* #if (NON_PREEMPTIVE == OSEK_ENABLE) */
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
