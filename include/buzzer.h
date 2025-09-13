#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <stdint.h>

void Buzzer_Setup();
void Buzzer_Freq(uint8_t freq);
void Buzzer_Volume(uint8_t volume);

#endif
