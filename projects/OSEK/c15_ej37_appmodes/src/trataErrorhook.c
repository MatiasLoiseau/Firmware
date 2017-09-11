
#include "sapi.h"
#include "os.h"       // <= freeOSEK

uint8_t OSErrorGetServiceIdTxt[][25]= {"Indefinida","ActivateTask","TerminateTask","ChainTask","Schedule",
                                       "GetTaskID","GetTaskState","DisableAllInterrupts","EnableAllInterrupts","SuspendAllInterrupts",
                                       "ResumeAllInterrupts","SuspendOSInterrupts","ResumeOSInterrupts","GetResource","ReleaseResource",
                                       "SetEvent","ClearEvent","GetEvent","WaitEvent","GetAlarmBase","GetAlarm","SetRelAlarm",
                                       "SetAbsAlarm","CancelAlarm","GetActiveApplicationMode","StartOS","ShutdownOS"
                                      };

uint8_t OSErrorGetRetTxt[][13]= {"E_OK","E_OS_ACCESS","E_OS_CALLEVEL","E_OS_ID",
                                 "E_OS_LIMIT","E_OS_NOFUNC","E_OS_RESOURCE","E_OS_STATE","E_OS_VALUE"
                                };

void trataErrorHook( void )
{
    uartWriteString( UART_USB, "\r\n------------------------------------------------------------\r\n" );
    uartWriteString( UART_USB, "ErrorHook fue llamado, Detalle de ERROR capturado:\r\n" );
    uartWriteString( UART_USB, "SERVICIO: " );
    uartWriteByte(   UART_USB, ( OSErrorGetServiceId()+48 ) );
    uartWriteString( UART_USB, "=" );
    uartWriteString( UART_USB, OSErrorGetServiceIdTxt[OSErrorGetServiceId()] );
    uartWriteString( UART_USB, "---> RETORNO: " );
    uartWriteByte(   UART_USB, ( OSErrorGetRet()+48 ) );
    uartWriteString( UART_USB, "=" );
    uartWriteString( UART_USB, OSErrorGetRetTxt[OSErrorGetRet()] );
    uartWriteString( UART_USB, "\r\n------------------------------------------------------------\r\n" );

    //de aca para abajo: tratamiento de Hooks que retornan sin shutdownOS y se manejan fuera.
    switch ( OSErrorGetServiceId() )
    {
        case ( OSServiceId_GetAlarm ):
            switch ( OSErrorGetRet() )
            {
                case ( E_OS_NOFUNC ):
                    break;
            }
            break;
        default:
            ShutdownOS( 0 );
    }
}

