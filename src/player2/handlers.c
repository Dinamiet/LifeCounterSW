#include "handlers.h"

#include "buzzer.h"
#include "display.h"

uint16_t life2 = 5;

void knobIncrement2(const void* _)
{
	(void)_; // Unused
	if (life2 < 100)
		Display_ShowUInt(DISPLAY2, ++life2);

	Buzzer_Freq(life2);
}

void knobDecrement2(const void* _)
{
	(void)_; // Unused

	if (life2 > 0)
		Display_ShowUInt(DISPLAY2, --life2);

	Buzzer_Freq(life2);
}

void buttonEvent2(const void* _)
{
	(void)_; // Unused
	// HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	Display_Clear(DISPLAY2);
}
