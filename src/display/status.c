#include "display.h"
#include "render.h"

void Display_ShowStatus(Display disp, uint8_t status)
{
	DisplayData* dispData = NULL;
	switch (disp)
	{
		case DISPLAY1:
			dispData = &display1;
			break;

		case DISPLAY2:
			dispData = &display2;
	}

	dispData->Status = status;
}
