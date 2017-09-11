/*
 * cc.h
 *
 *  Created on: 31/8/2017
 *      Author: Mauricio
 */

#ifndef CC_H_
#define CC_H_

#define CC_FLAG_LLENO	0x00000001
#define CC_FLAG_VACIO	0x00000002

typedef struct
{
    uint8_t * p_buf; /* puntero a pool de memoria que utilizará la instancia para almacenar los datos. */
    uint8_t * p_put; /* puntero al elemento dentro del pool en el cual agregar el proximo dato */
    uint8_t * p_get; /* puntero al elemento dentro del pool que esta primero para ser removido */
    uint8_t tam_buf; /* tamaño del pool de memoria*/
    uint8_t flags;	 /* flags de estado del la instancia del ADT */

    EventMaskType EventoEsperarEspacio;
    TaskType 	TareaEsperandoEspacio;

    EventMaskType EventoEsperarDato;
    TaskType 	TareaEsperandoDato;
} ccADT8_t;

void cc8_Config ( ccADT8_t *, uint8_t *, uint8_t );
void cc8_Write( ccADT8_t *, uint8_t * );
void cc8_Read( ccADT8_t *, uint8_t * );

#endif /* CC_H_ */
