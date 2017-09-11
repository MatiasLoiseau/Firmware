/*
 *  Implementa Cola Circular como ADT (tipo de dato abstracto)
 *  Created on: 31/8/2017
 *      Author: Mauricio
 */

#include "sapi.h"         /* <= sAPI header */
#include "cc.h"
#include "os.h"

/*
 * Temas a considerar:
 *   - Bloqueo
 *   - Integracion con OSEK
 *   - Concurrencia
 * */
void cc8_Config ( ccADT8_t * ccStruct, uint8_t * buffer, uint8_t tam )
{
	SuspendAllInterrupts();

    ccStruct->p_buf=buffer;
    ccStruct->p_get=buffer;
    ccStruct->p_put=buffer;
    ccStruct->tam_buf=tam;
    ccStruct->flags=0;

    ccStruct->TareaEsperandoEspacio = INVALID_TASK;
    ccStruct->TareaEsperandoDato    = INVALID_TASK;

    ResumeAllInterrupts();
}

/* */
void cc8_Write( ccADT8_t * ccStruct, uint8_t * dato )
{
    uint8_t* p_aux;

    SuspendAllInterrupts();

    p_aux = ccStruct->p_put;
    p_aux++;

    if( p_aux == ( ccStruct->p_buf + ccStruct->tam_buf ) )
    {
        p_aux = ccStruct->p_buf;               //el ptr de ESCRITURA se dio la vuelta
    }

    if ( p_aux == ccStruct->p_get )          //veo si esta LLENO
    {
        ccStruct->flags |= CC_FLAG_LLENO ;   //error por esta LLENO

        GetTaskID( &ccStruct->TareaEsperandoEspacio );

        ResumeAllInterrupts();

        WaitEvent( ccStruct->EventoEsperarEspacio );
        ClearEvent( ccStruct->EventoEsperarEspacio );

        SuspendAllInterrupts();

        ccStruct->TareaEsperandoEspacio = INVALID_TASK;
    }
    else
    {
        *( p_aux )= * dato;
        ccStruct->p_put=p_aux;
        ccStruct->flags &= ~CC_FLAG_LLENO ;   //ESCRIBIO OK
    }

    if( ccStruct->TareaEsperandoDato != INVALID_TASK )
	 {
		SetEvent( ccStruct->TareaEsperandoDato , ccStruct->EventoEsperarDato );
	 }

    ResumeAllInterrupts();
}

void cc8_Read( ccADT8_t * ccStruct, uint8_t * dato )
{
    SuspendAllInterrupts();

    if( ccStruct->p_put == ccStruct->p_get )    //veo si esta VACIO
    {
        ccStruct->flags |= CC_FLAG_VACIO ;      //error por esta VACIO

		GetTaskID( &ccStruct->TareaEsperandoDato );

        ResumeAllInterrupts();

		WaitEvent( ccStruct->EventoEsperarDato );
		ClearEvent( ccStruct->EventoEsperarDato );

	    SuspendAllInterrupts();

		ccStruct->TareaEsperandoDato = INVALID_TASK;
    }
    else
    {
        ccStruct->p_get++;

        if( ccStruct->p_get == ( ccStruct->p_buf + ccStruct->tam_buf ) )
        {
            ccStruct->p_get=ccStruct->p_buf;    //el ptr de LECTURA se dio la vuelta
        }

        * dato= *( ccStruct->p_get );

        ccStruct->flags &= ~CC_FLAG_VACIO ;      //LECTURA OK
    }

    if( ccStruct->TareaEsperandoEspacio != INVALID_TASK )
    {
    	SetEvent( ccStruct->TareaEsperandoEspacio , ccStruct->EventoEsperarEspacio );
    }

    ResumeAllInterrupts();
}

