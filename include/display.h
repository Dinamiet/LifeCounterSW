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
void Display_Enable(bool enable);
void Display_ShowInt(Display disp, uint16_t value);

#endif
