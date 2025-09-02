#include "display.h"
#include "gpio.h"
#include "main.h"
#include "render.h"
#include "tasks.h"

#include <string.h>

void Display_Setup()
{
	Display_Clear(DISPLAY1);
	Display_Clear(DISPLAY2);
	Display_Enable(false);

	memset(&display1, 0, sizeof(display1));
	memset(&display2, 0, sizeof(display2));

	Scheduler_CreateRecurringTask(&scheduler, &renderTask, TASK_RENDER, display_Render, NULL, RENDER_PERIOD);
}

void Display_Enable(bool enable) { HAL_GPIO_WritePin(DispOE_GPIO_Port, DispOE_Pin, !enable); }
