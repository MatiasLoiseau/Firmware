/* Copyright 2017,
 *
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
#ifndef LED_H
#define LED_H


/*==================[inclusions]=============================================*/
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define LEDROJO_GRUPO 2
#define LEDROJO_GRUPO 
#define LEDROJO_GRUPO 2
#define LEDROJO_GRUPO 2

#define LEDVERDE

#define LEDAZUL

#define OUTPUT_DIRECTION   1
#define INPUT_DIRECTION    0

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
/** \brief Definition of constants to reference the EDU-CIAA leds.
 **
 **/
enum LED_COLOR {RGB_R_LED, RGB_G_LED, RGB_B_LED, RED_LED, YELLOW_LED, GREEN_LED};


/** \brief Definition of constants to control the EDU-CIAA leds.
 **
 **/
enum LED_STATUS {OFF, ON};

/*==================[external functions declaration]=========================*/

void init_led(void);
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_toggle(uint8_t led);


/*==================[end of file]============================================*/
#endif /* #ifndef LED_H */

