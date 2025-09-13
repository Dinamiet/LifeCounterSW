#include "handlers.h"

#include "buzzer.h"
#include "display.h"

uint16_t life = 10;

void knobIncrement(const void* _)
{
	(void)_; // Unused
	if (life < 100)
		Display_ShowUInt(DISPLAY1, ++life);

	// Display_Brightness(life);
	Buzzer_Volume(life);
}

void knobDecrement(const void* _)
{
	(void)_; // Unused

	if (life > 0)
		Display_ShowUInt(DISPLAY1, --life);

	// Display_Brightness(life);
	Buzzer_Volume(life);
}

void buttonEvent(const void* _)
{
	(void)_; // Unused

	// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
	// HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	Display_Clear(DISPLAY1);
}
