#include "display.h"

#include "render.h"

static uint8_t lookup[16] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x67, // 9
	0x77, // A
	0x7C, // B
	0x39, // C
	0x5E, // D
	0x79, // E
	0x71, // F
};

void Display_ShowUInt(EventSide side, uint16_t value)
{
	DisplayData* dispData = &display[side];

	for (uint8_t i = 0; i < NUM_DIGITS; i++)
	{
		uint8_t segmentData = lookup[value%10];

		// Remove leading zeros, but keep single zero
		dispData->Digit[NUM_DIGITS-1-i] = (value > 0 || i == 0 ) ? segmentData : 0;

		value /= 10;
	}
}
