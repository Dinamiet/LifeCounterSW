#include "buzzer.h"
#include "tim.h"

#define FREQ_OFFSET 2

void Buzzer_SetFreq(uint8_t freq)
{
	if (freq > 100)
		freq = 100;

	htim3.Instance->PSC = freq + FREQ_OFFSET;
}

uint8_t Buzzer_GetFreq() { return htim3.Instance->PSC - FREQ_OFFSET; }
