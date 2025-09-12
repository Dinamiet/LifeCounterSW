#include "handlers.h"
#include "display.h"
#include "tim.h"

uint16_t life = 0;

void knobIncrement(const void* _)
{
	(void)_; // Unused
	if (life < 9999)
		Display_ShowUInt(DISPLAY1, ++life);

	// htim3.Instance->ARR = life; // Period
}

void knobDecrement(const void* _)
{
	(void)_; // Unused

	if (life > 0)
		Display_ShowUInt(DISPLAY1, --life);

	// htim3.Instance->ARR = life; // Period
}

void buttonEvent(const void* _)
{
	(void)_; // Unused

	// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
	// HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	Display_Clear(DISPLAY1);
}
