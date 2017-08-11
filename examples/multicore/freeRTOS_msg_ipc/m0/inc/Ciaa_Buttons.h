/*
 * Ciaa_Buttons.h
 *
 *  Created on: 7 May 2016
 *      Author: Martin Fernández
 */

#ifndef CIAA_BUTTONS_H_
#define CIAA_BUTTONS_H_

#include "chip.h"

/** port and pin numbers were extracted from edu-ciaa's pinout sheet
* TEC_1 == SW_1
*/

#define SW_PORT 	1
#define SW_1_PIN 	0
#define SW_2_PIN 	1
#define SW_3_PIN 	2
#define SW_4_PIN 	6

#define SW_1_GPIO_PORT		0
#define SW_1_GPIO_BIT 		4
#define SW_2_GPIO_PORT	 	0
#define SW_2_GPIO_BIT 		8
#define SW_3_GPIO_PORT 		0
#define SW_3_GPIO_BIT 		9
#define SW_4_GPIO_PORT 		1
#define SW_4_GPIO_BIT 		9

typedef enum {
	TEC1 = 0x01,
	TEC2 = 0x02,
	TEC3 = 0x04,
	TEC4 = 0x08
}buttonstecnum_t ;

/**
 * @brief	returns buttons state on board
 * @return	returns an 8bit integer whose lower 4 bits logic states correspond with the state of each button on the board
 * eg. if SW_1 has been pressed the function will return 0x01. If both SW_1 and SW_3 has been pressed it will return 0x05.
 */
uint8_t Ciaa_Buttons_GetStatus(void);

/**
 * @brief	initialize buttons interface on board
 * @return	nothing
 */
void Ciaa_Buttons_Init(void);

#endif /* CIAA_BUTTONS_H_ */
