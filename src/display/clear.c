#include "display.h"
#include "main.h"
#include "gpio.h"

void Display_Clear(Display disp)
{
	switch (disp)
	{
	case DISPLAY1:
		HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_SET);
		break;

	case DISPLAY2:
		HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_SET);
		break;
	}
}
