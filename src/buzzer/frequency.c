#include "buzzer.h"
#include "tim.h"

void Buzzer_Freq(uint8_t freq)
{
	if (freq > 100)
		freq = 100;

	htim3.Instance->PSC = freq+2;
}
