#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <stdbool.h>

#define MAX_BUTTONS 2
#define MAX_KNOBS   2

typedef enum _Buttons_
{
	BUTTON_1,
	BUTTON_2,
} Buttons;

typedef enum _Knobs_
{
	KNOB_1,
	KNOB_2,
} Knobs;

typedef enum _Events_
{
	EVENT_BUTTON,
	EVENT_KNOB,

	EVENT_BUTTON_LONG_PRESS,
	EVENT_BUTTON_DOUBLE_PRESS,
} Events;

typedef union _EventData_
{
	struct
	{
		Buttons Button;
		bool    State;
	};
	struct
	{
		Knobs Knob;
		bool  Increasing;
	};
} EventData;

#endif
