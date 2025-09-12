#include "handlers.h"
#include "display.h"

#include "tim.h"

uint16_t life2 = 0;

void knobIncrement2(const void* _)
{
	(void)_; // Unused
	if (life2 < 9999)
		Display_ShowUInt(DISPLAY2, ++life2);

	// htim3.Instance->CCR2 = life2; // Duty
}

void knobDecrement2(const void* _)
{
	(void)_; // Unused

	if (life2 > 0)
		Display_ShowUInt(DISPLAY2, --life2);

	// htim3.Instance->CCR2 = life2; // Duty
}

void buttonEvent2(const void* _)
{
	(void)_; // Unused
	// HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	Display_Clear(DISPLAY2);
}
