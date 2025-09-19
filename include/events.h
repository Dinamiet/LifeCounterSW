#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <stdbool.h>

typedef enum _EventSide_
{
	EVENTSIDE_1,
	EVENTSIDE_2,
	EVENTSIDE_MAX
} EventSide;

typedef enum _Events_
{
	EVENT_BUTTON,
	EVENT_KNOB,

	EVENT_BUTTON_SINGLE_PRESS,
	EVENT_BUTTON_LONG_PRESS,
	EVENT_BUTTON_DOUBLE_PRESS,
} Events;

typedef struct _EventData_
{
	EventSide Side;
	union
	{
		bool  State;
		bool  Increasing;
	};
} EventData;

#endif
