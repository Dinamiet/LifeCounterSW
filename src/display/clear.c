#include "display.h"
#include "gpio.h"
#include "main.h"
#include "render.h"

#include <string.h>

void Display_Clear(EventSide side)
{
	memset(&display[side], 0, sizeof(display[side]));
	switch (side)
	{
		case EVENTSIDE_1:
			HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_SET);
			break;

		case EVENTSIDE_2:
			HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_SET);
			break;

		case EVENTSIDE_MAX:
			break; // Ignore
	}
}
