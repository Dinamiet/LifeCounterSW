#include "buzzer.h"
#include "tim.h"

void Buzzer_Volume(uint8_t volume)
{
	if (volume > 100)
		volume = 100;
	htim3.Instance->CCR2 = volume;
}
