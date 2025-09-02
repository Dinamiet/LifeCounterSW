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
DisplayData   display1;
DisplayData   display2;

void display_Render(void* _)
{
	(void)_; // Unused parameter
	static RenderIndex index = {.Value = 0};

	DisplayData*  dispData  = NULL;
	GPIO_TypeDef* gpio_port = NULL;

	switch (index.DisplayNum)
	{
		case 0:
			dispData  = &display1;
			gpio_port = Disp1LAT_GPIO_Port;
			break;

		case 1:
			dispData  = &display2;
			gpio_port = Disp2LAT_GPIO_Port;
			break;
	}

	struct
	{
		uint8_t ActiveDigit : 4;
		uint8_t StatusLEDs  : 4;
		uint8_t Value       : 7;
		uint8_t Point       : 1;
	} data;

	data.StatusLEDs  = dispData->Status;
	data.ActiveDigit = 1 << index.DigitNum;
	data.Value       = ~(dispData->Digit[index.DigitNum]);
	data.Point       = ((~dispData->Point) >> index.DigitNum) & 0x01;

	HAL_GPIO_WritePin(gpio_port, DispLAT_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&data, sizeof(data), 1);
	HAL_GPIO_WritePin(gpio_port, DispLAT_Pin, GPIO_PIN_SET);

	index.Value++;
}
