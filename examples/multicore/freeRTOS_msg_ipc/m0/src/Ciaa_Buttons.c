/*
 * Ciaa_Buttons.c
 *
 *  Created on: 7 May 2016
 *      Author: martin
 */
/*
 * Ciaa_Buttons.c
 *
 *  Created on: 7 May 2016
 *      Author: Martin Fernández
 */

/*==================[inclusions]=============================================*/

#include "Ciaa_Buttons.h"

#include "chip.h"
#include "board.h"

void Ciaa_Buttons_Init(void)
{
	Chip_SCU_PinMux(SW_PORT,SW_1_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[4], SW_1 */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, SW_1_GPIO_PORT, SW_1_GPIO_BIT);	// input

	Chip_SCU_PinMux(SW_PORT,SW_2_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[8], SW_2 */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, SW_2_GPIO_PORT, SW_2_GPIO_BIT);	// input

	Chip_SCU_PinMux(SW_PORT,SW_3_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[9], SW_3 */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, SW_3_GPIO_PORT, SW_3_GPIO_BIT);	// input

	Chip_SCU_PinMux(SW_PORT,SW_4_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO1[9], SW_4 */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, SW_4_GPIO_PORT, SW_4_GPIO_BIT);	// input

}

uint8_t Ciaa_Buttons_GetStatus(void)
{
	uint8_t status = 0x00;

	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, SW_1_GPIO_PORT, SW_1_GPIO_BIT) == 0)
	{
		status |= TEC1;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, SW_2_GPIO_PORT, SW_2_GPIO_BIT) == 0)
	{
		status |= TEC2;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, SW_3_GPIO_PORT, SW_3_GPIO_BIT) == 0)
	{
		status |= TEC3;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, SW_4_GPIO_PORT, SW_4_GPIO_BIT) == 0)
	{
		status |= TEC4;
	}

	return status;
}

