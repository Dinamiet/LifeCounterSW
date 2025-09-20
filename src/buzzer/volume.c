#include "buzzer.h"
#include "tim.h"

void Buzzer_SetVolume(uint8_t volume)
{
	if (volume > 100)
		volume = 100;
	htim3.Instance->CCR2 = volume;
}

uint8_t Buzzer_GetVolume() { return htim3.Instance->CCR2; }
