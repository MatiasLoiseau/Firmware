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
/** \brief TareaUART stack */
#if ( x86 == ARCH )
uint8 StackTaskTareaUART[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskTareaUART[512];
#endif
/** \brief CCIngresaD stack */
#if ( x86 == ARCH )
uint8 StackTaskCCIngresaD[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskCCIngresaD[512];
#endif
/** \brief CCSacaD stack */
#if ( x86 == ARCH )
uint8 StackTaskCCSacaD[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskCCSacaD[512];
#endif
/** \brief CCInicia stack */
#if ( x86 == ARCH )
uint8 StackTaskCCInicia[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskCCInicia[512];
#endif

/** \brief TareaUART context */
TaskContextType ContextTaskTareaUART;
/** \brief CCIngresaD context */
TaskContextType ContextTaskCCIngresaD;
/** \brief CCSacaD context */
TaskContextType ContextTaskCCSacaD;
/** \brief CCInicia context */
TaskContextType ContextTaskCCInicia;

/** \brief Ready List for Priority 3 */
TaskType ReadyList3[1];

/** \brief Ready List for Priority 2 */
TaskType ReadyList2[1];

/** \brief Ready List for Priority 1 */
TaskType ReadyList1[1];

/** \brief Ready List for Priority 0 */
TaskType ReadyList0[1];

const AlarmType OSEK_ALARMLIST_HardwareCounter[1] = {
   Alarma_Tarea_UART, /* this alarm has to be incremented with this counter */
};


/*==================[external data definition]===============================*/
/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.         Osek P.
 * 30               3
 * 20               2
 * 10               1
 * 3               0
 */

const TaskConstType TasksConst[TASKS_COUNT] = {
   /* Task TareaUART */
   {
       OSEK_TASK_TareaUART,   /* task entry point */
       &ContextTaskTareaUART, /* pointer to task context */
       StackTaskTareaUART, /* pointer stack memory */
       sizeof(StackTaskTareaUART), /* stack size */
       2, /* task priority */
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
   /* Task CCIngresaD */
   {
       OSEK_TASK_CCIngresaD,   /* task entry point */
       &ContextTaskCCIngresaD, /* pointer to task context */
       StackTaskCCIngresaD, /* pointer stack memory */
       sizeof(StackTaskCCIngresaD), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | EventoEsc | EventoHayLugar , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task CCSacaD */
   {
       OSEK_TASK_CCSacaD,   /* task entry point */
       &ContextTaskCCSacaD, /* pointer to task context */
       StackTaskCCSacaD, /* pointer stack memory */
       sizeof(StackTaskCCSacaD), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | EventoLee | EventoMasDatos , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task CCInicia */
   {
       OSEK_TASK_CCInicia,   /* task entry point */
       &ContextTaskCCInicia, /* pointer to task context */
       StackTaskCCInicia, /* pointer stack memory */
       sizeof(StackTaskCCInicia), /* stack size */
       3, /* task priority */
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

/** \brief List of Auto Start Tasks in Application Mode AppMode1 */
const TaskType TasksAppModeAppMode1[2]  = {
   CCIngresaD,
   CCSacaD
};
/** \brief AutoStart Array */
const AutoStartType AutoStart[1]  = {
   /* Application Mode AppMode1 */
   {
      2, /* Total Auto Start Tasks in this Application Mode */
      (TaskRefType)TasksAppModeAppMode1 /* Pointer to the list of Auto Start Stacks on this Application Mode */
   }
};

const ReadyConstType ReadyConst[4] = { 
   {
      1, /* Length of this ready list */
      ReadyList3 /* Pointer to the Ready List */
   },
   {
      1, /* Length of this ready list */
      ReadyList2 /* Pointer to the Ready List */
   },
   {
      1, /* Length of this ready list */
      ReadyList1 /* Pointer to the Ready List */
   },
   {
      1, /* Length of this ready list */
      ReadyList0 /* Pointer to the Ready List */
   }
};

/** TODO replace next line with: 
 ** ReadyVarType ReadyVar[4] ; */
ReadyVarType ReadyVar[4];

/** \brief Resources Priorities */
const TaskPriorityType ResourcesPriority[0]  = {

};
/** TODO replace next line with: 
 ** AlarmVarType AlarmsVar[1]; */
AlarmVarType AlarmsVar[1];

const AlarmConstType AlarmsConst[1]  = {
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         TareaUART, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   }
};

const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {
  {
      AppMode1, /* Application Mode */
      Alarma_Tarea_UART, /* Alarms */
      0, /* Alarm Time */
      40 /* Alarm Time */
   }
};

CounterVarType CountersVar[1];

const CounterConstType CountersConst[1] = {
   {
      1, /* quantity of alarms for this counter */
      (AlarmType*)OSEK_ALARMLIST_HardwareCounter, /* alarms list */
      1000000, /* max allowed value */
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

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

