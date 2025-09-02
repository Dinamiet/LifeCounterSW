#ifndef _RENDER_H_
#define _RENDER_H_

#include "utilities.h"

#define NUM_DIGITS 4

extern SchedulerTask renderTask;

typedef struct _DisplayData_
{
	uint8_t Digit[NUM_DIGITS];
	uint8_t Point  : 4;
	uint8_t Status : 4;
} DisplayData;

extern DisplayData display1;
extern DisplayData display2;

void display_Render(void* _);

#endif
