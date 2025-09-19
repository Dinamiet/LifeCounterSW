#include "counter.h"
#include "display.h"
#include "utilities.h"

#include <stdint.h>

#define COUNTER_MAX 9999
#define COUNTER_MIN 0

uint8_t currentCounter[EVENTSIDE_MAX] = {0};
uint16_t counter[EVENTSIDE_MAX][MAX_COUNTERS] = {0};

ObserverSubscription counterSwitchWatcher;
ObserverSubscription counterChangeWatcher;

static void nextCounter_Handler(const void* data);
static void changeCounter_Handler(const void* data);

static void nextCounter_Handler(const void* data)
{
	EventSide side = *(EventSide*)data;

	currentCounter[side] = (currentCounter[side] + 1) % MAX_COUNTERS;
	Display_ShowStatus(side, 1 << currentCounter[side]);
	Display_ShowUInt(side, counter[side][currentCounter[side]]);
}

static void changeCounter_Handler(const void* data)
{
	EventData* event = (EventData*)data;

	switch (event->Increasing)
	{
	case true:
		if (counter[event->Side][currentCounter[event->Side]] < COUNTER_MAX)
			++counter[event->Side][currentCounter[event->Side]];
		break;

	case false:
		if (counter[event->Side][currentCounter[event->Side]] > COUNTER_MIN)
			--counter[event->Side][currentCounter[event->Side]];
		break;
	}

	Display_ShowUInt(event->Side, counter[event->Side][currentCounter[event->Side]]);
}

void Counter_Init()
{
	Display_ShowStatus(EVENTSIDE_1, 1 << currentCounter[EVENTSIDE_1]);
	Display_ShowStatus(EVENTSIDE_2, 1 << currentCounter[EVENTSIDE_2]);

	Observer_Subscribe(&eventNotifier, &counterSwitchWatcher, EVENT_BUTTON_SINGLE_PRESS, nextCounter_Handler);
	Observer_Subscribe(&eventNotifier, &counterChangeWatcher, EVENT_KNOB, changeCounter_Handler);
}
