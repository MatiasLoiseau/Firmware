/* Copyright 2016, Martin Fernandez
 * All rights reserved.
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


#ifndef UART_FREERTOS_DRIVER_MF_H_
#define UART_FREERTOS_DRIVER_MF_H_

#include "../../../freeRTOS_fir/m0/inc/FreeRTOSConfig.h"
#include "board.h"
#include "chip.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"

typedef enum _uarts
{
	UART0 = 0,
	UART2 = 1,
	UART3 = 2
}uarts_e;

void UART_BaudsConfig(uarts_e , uint32_t );
void UART_RS485Enable(uarts_e );

int32_t UART_freeRTOS_Init(uarts_e );
void UART_freeRTOS_Deinit(uarts_e );

uint32_t UART_freeRTOS_DataCount(uarts_e );

uint32_t UART_freeRTOS_GetData(uarts_e , uint8_t * );
uint32_t UART_freeRTOS_GetNBytes(uarts_e , uint8_t * , uint32_t );

int32_t UART_freeRTOS_WriteNBytes(uarts_e , uint8_t * , uint32_t );

#endif /* UART_FREERTOS_DRIVER_MF_H_ */
