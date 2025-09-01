#include "display.h"
#include "gpio.h"
#include "main.h"
#include "tasks.h"

#include "render.h"

void Display_Setup()
{
	Display_Clear(DISPLAY1);
	Display_Clear(DISPLAY2);
	Display_Enable(false);

	Scheduler_CreateRecurringTask(&scheduler, &renderTask, TASK_RENDER, display_Render, NULL, RENDER_PERIOD);
}

void Display_Enable(bool enable) { HAL_GPIO_WritePin(DispOE_GPIO_Port, DispOE_Pin, !enable); }
