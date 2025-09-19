#include "trigger.h"

#include "events.h"
#include "tasks.h"
#include "utilities.h"

#define LONG_PRESS_TIME       500
#define EXTRA_LONG_PRESS_TIME 5000

static ObserverSubscription btnEventNotifier;
static uint32_t             btnDownTime[EVENTSIDE_MAX];

static void btnEvent_Handler(const void* data);

static void btnEvent_Handler(const void* data)
{
	const EventData* event = data;

	uint32_t now      = Utilities_GetTime();
	uint32_t downTime = now - btnDownTime[event->Side];

	switch (event->State)
	{
		case true:
			btnDownTime[event->Side] = now;
			break;

		case false:
			if (downTime > EXTRA_LONG_PRESS_TIME)
				Observer_Publish(&eventNotifier, EVENT_BUTTON_EXTRA_LONG_PRESS, &event->Side);
			else if (downTime > LONG_PRESS_TIME)
				Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, &event->Side);
			else
				Observer_Publish(&eventNotifier, EVENT_BUTTON_SINGLE_PRESS, &event->Side);

			break;
	}
}

void Trigger_Setup() { Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler); }
