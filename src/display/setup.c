#include "display.h"
#include "gpio.h"
#include "main.h"
#include "render.h"
#include "tasks.h"
#include "tim.h"

#include <string.h>

void Display_Setup()
{
	Display_Clear(DISPLAY1);
	Display_Clear(DISPLAY2);

	memset(&display1, 0, sizeof(display1));
	memset(&display2, 0, sizeof(display2));

	Scheduler_CreateRecurringTask(&scheduler, &renderTask, TASK_RENDER, display_Render, NULL, RENDER_PERIOD);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
}

void Display_Brightness(uint16_t brightness) { htim16.Instance->CCR1 = brightness; }
