#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <stdint.h>

void Buzzer_Setup();
void    Buzzer_SetFreq(uint8_t freq);
uint8_t Buzzer_GetFreq();
void    Buzzer_SetVolume(uint8_t volume);
uint8_t Buzzer_GetVolume();

#endif
