#include "main.h"

#include "display.h"
#include "encoder.h"
#include "gpio.h"
#include "i2c.h"
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

	Scheduler_Setup();
	Heartbeat_Setup();

	Display_Setup();

	Display_Enable(true);

	Encoder_Setup();

	while (true)
	{
		SchedulerTask* task = Scheduler_NextReady(&scheduler);
		Scheduler_Execute(task);
		Scheduler_Queue(&scheduler, task);
	}

	return 0;
}
