#include "counter.h"

#include "display.h"
#include "utilities.h"

#include <stdint.h>

#define COUNTER_MAX 9999
#define COUNTER_MIN 0

typedef struct _Counter_
{
	bool     Active;
	uint8_t  CurrentShown;
	uint16_t Values[MAX_COUNTERS];
} Counter;

static ObserverSubscription counterSwitchWatcher;
static ObserverSubscription counterChangeWatcher;
static ObserverSubscription counterJumpWatcher;

static Counter counter[EVENTSIDE_MAX];

static void nextCounter_Handler(const void* data);
static void changeCounter_Handler(const void* data);
static void jumpCounter_Handler(const void* data);

static void nextCounter_Handler(const void* data)
{
	EventSide side = *(EventSide*)data;

	if (!counter[side].Active)
		return;

	uint8_t shown = (counter[side].CurrentShown + 1) % MAX_COUNTERS;

	counter[side].CurrentShown = shown;
	Display_ShowStatus(side, 1 << shown);
	Display_ShowUInt(side, counter[side].Values[shown]);
}

static void changeCounter_Handler(const void* data)
{
	EventData* event = (EventData*)data;

	if (!counter[event->Side].Active)
		return;

	uint8_t shown = counter[event->Side].CurrentShown;
	switch (event->Increasing)
	{
		case true:
			if (counter[event->Side].Values[shown] < COUNTER_MAX)
				++counter[event->Side].Values[shown];
			break;

		case false:
			if (counter[event->Side].Values[shown] > COUNTER_MIN)
				--counter[event->Side].Values[shown];
			break;
	}

	Display_ShowUInt(event->Side, counter[event->Side].Values[shown]);
}

static void jumpCounter_Handler(const void* data)
{
	EventSide side = *(EventSide*)data;

	if (!counter[side].Active)
		return;

	uint8_t  shown = counter[side].CurrentShown;
	uint16_t jump  = counter[side].Values[shown] * 10;

	if (jump > COUNTER_MAX)
		jump = 0;

	counter[side].Values[shown] = jump;
	Display_ShowUInt(side, counter[side].Values[shown]);
}

void Counter_Init()
{
	for (EventSide side = 0; side < EVENTSIDE_MAX; ++side)
	{
		counter[side].Active       = true;
		counter[side].CurrentShown = 0;
		for (uint8_t i = 0; i < MAX_COUNTERS; ++i) counter[side].Values[i] = 0;
		Display_ShowStatus(side, 1 << counter[side].CurrentShown);
		Display_ShowUInt(side, counter[side].Values[counter[side].CurrentShown]);
	}

	Observer_Subscribe(&eventNotifier, &counterSwitchWatcher, EVENT_BUTTON_SINGLE_PRESS, nextCounter_Handler);
	Observer_Subscribe(&eventNotifier, &counterChangeWatcher, EVENT_KNOB, changeCounter_Handler);
	Observer_Subscribe(&eventNotifier, &counterJumpWatcher, EVENT_BUTTON_LONG_PRESS, jumpCounter_Handler);
}

void Counter_Active(EventSide side, bool active)
{
	counter[side].Active = active;
	if (active)
	{
		Display_ShowStatus(side, 1 << counter[side].CurrentShown);
		Display_ShowUInt(side, counter[side].Values[counter[side].CurrentShown]);
	}
}
