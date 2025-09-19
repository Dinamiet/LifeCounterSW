#include "display.h"
#include "gpio.h"
#include "main.h"
#include "render.h"
#include "tasks.h"
#include "tim.h"

#include <string.h>

void Display_Setup()
{
	Display_Clear(EVENTSIDE_1);
	Display_Clear(EVENTSIDE_2);

	memset(display, 0, sizeof(display));

	Scheduler_CreateRecurringTask(&scheduler, &renderTask, TASK_RENDER, display_Render, NULL, RENDER_PERIOD);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
}

void Display_Brightness(uint8_t brightness)
{
	if (brightness > 100)
		brightness = 100;

	htim16.Instance->CCR1 = brightness;
}
