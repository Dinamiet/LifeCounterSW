#include "handlers.h"

#include "buzzer.h"
#include "display.h"

uint16_t life             = 10;
bool     adjustBrightness = false;

void knobIncrement(const void* _)
{
	(void)_; // Unused
	if (life < 100)
		Display_ShowUInt(DISPLAY1, ++life);

	if (adjustBrightness)
		Display_Brightness(life);
	else
		Buzzer_Volume(life);
}

void knobDecrement(const void* _)
{
	(void)_; // Unused

	if (life > 0)
		Display_ShowUInt(DISPLAY1, --life);

	if (adjustBrightness)
		Display_Brightness(life);
	else
		Buzzer_Volume(life);
}

void buttonEvent(const void* btnState)
{
	const bool* state = btnState;
	if (*state)
		adjustBrightness = !adjustBrightness;
	// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
	// HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	// Display_Clear(DISPLAY1);
	Display_ShowStatus(DISPLAY1, adjustBrightness);
}
