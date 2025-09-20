#include "main.h"

#include "buzzer.h"
#include "config.h"
#include "display.h"
#include "encoder.h"
#include "gpio.h"
#include "i2c.h"
#include "navigation.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "utilities.h"

#include <stdbool.h>

int main()
{
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_SPI1_Init();
	MX_USART1_UART_Init();
	MX_TIM3_Init();
	MX_TIM16_Init();

	Utilities_Setup();

	Display_Setup();

	Encoder_Setup();

	Navigation_Setup();

	Buzzer_Setup();

	Config_Load();

	while (true)
	{
		SchedulerTask* task = Scheduler_NextReady(&scheduler);
		Scheduler_Execute(task);
		Scheduler_Queue(&scheduler, task);
	}

	return 0;
}
