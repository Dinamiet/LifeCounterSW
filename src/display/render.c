#include <stdint.h>
#include "main.h"
#include "gpio.h"
#include "spi.h"

#include "render.h"

typedef union _RenderIndex_
{
	struct
	{
		uint8_t Value : 3;
		uint8_t       : 5;
	};
	struct
	{
		uint8_t DisplayNum : 1;
		uint8_t DigitNum   : 2;
	};

} RenderIndex;

SchedulerTask renderTask;

void display_Render(void* _)
{
	(void)_; // Unused parameter
	static RenderIndex index = {.Value = 0};

	struct
	{
		uint8_t ActiveDigit : 4;
		uint8_t StatusLEDs  : 4;
		uint8_t Value       : 7;
		uint8_t Point       : 1;
	} data;

	data.StatusLEDs = 0;
	data.ActiveDigit = 1 << index.DigitNum;
	data.Value = ~(0x3F);
	data.Point = 1;

	switch (index.DisplayNum)
	{
		case 0:
			HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi1, (uint8_t*)&data, sizeof(data), 1);
			HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_SET);
			break;

		case 1:
			HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi1, (uint8_t*)&data, sizeof(data), 1);
			HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_SET);
			break;
	}

	index.Value++;
}
