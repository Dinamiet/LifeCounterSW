#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum _Display_
{
	DISPLAY1,
	DISPLAY2,
} Display;

void Display_Setup();

void Display_Clear(Display disp);
void Display_Brightness(uint8_t brightness);
void Display_ShowUInt(Display disp, uint16_t value);

#endif
