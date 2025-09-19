#ifndef _MODE_H_
#define _MODE_H_

#include "events.h"

typedef enum _NavMode_
{
	MODE_COUNTER,
	MODE_SETTING,
	MODE_MAX,
} NavMode;

void Mode_Setup();
void Mode_Change(EventSide side, NavMode mode);

#endif
