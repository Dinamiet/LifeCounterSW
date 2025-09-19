#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "events.h"

#include <stdbool.h>
#include <stdint.h>

void Display_Setup();

void Display_Clear(EventSide side);
void    Display_SetBrightness(uint8_t brightness);
uint8_t Display_GetBrightness();
void Display_ShowUInt(EventSide side, uint16_t value);
void Display_ShowStatus(EventSide side, uint8_t status);

#endif
