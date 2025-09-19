#include "trigger.h"

#include "events.h"
#include "tasks.h"
#include "utilities.h"

#define ENABLE_DOUBLE_PRESS false

static ObserverSubscription btnEventNotifier;
#if ENABLE_DOUBLE_PRESS
static SchedulerTask btnDoublePressTask[EVENTSIDE_MAX];
#endif
static SchedulerTask btnLongPressTask[EVENTSIDE_MAX];

static EventSide sides[EVENTSIDE_MAX] = {EVENTSIDE_1, EVENTSIDE_2};
#if ENABLE_DOUBLE_PRESS
static bool withinDoublePressTime[EVENTSIDE_MAX] = {false};
#endif

static void btnEvent_Handler(const void* data);
static void btnLongPress_TaskHandler(void* data);
#if ENABLE_DOUBLE_PRESS
static void btnDoublePress_TaskHandler(void* data);
#endif

static void btnEvent_Handler(const void* data)
{
	const EventData* event = data;

	switch (event->State)
	{
		case true:
			// Setup and handle LONG presses
			if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Side) == &btnLongPressTask[event->Side])
				Scheduler_Refresh(&scheduler, &btnLongPressTask[event->Side]);
			else
				Scheduler_CreateSingleTask(&scheduler, &btnLongPressTask[event->Side], TASK_BTN_LONG_PRESS + event->Side, btnLongPress_TaskHandler, &sides[event->Side], BUTTON_LONG_PRESS);

			// Setup and handle DOUBLE presses
#if ENABLE_DOUBLE_PRESS
			if (withinDoublePressTime[event->Side])
			{
				withinDoublePressTime[event->Side] = false; // Reset the flag
				Scheduler_Remove(&scheduler, &btnDoublePressTask[event->Side]);
				Observer_Publish(&eventNotifier, EVENT_BUTTON_DOUBLE_PRESS, &event->Side);
			}
			else
#endif
				Observer_Publish(&eventNotifier, EVENT_BUTTON_SINGLE_PRESS, &event->Side);
			break;

		case false:
			// Setup and handle LONG presses
			if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Side) == &btnLongPressTask[event->Side])
				Scheduler_Remove(&scheduler, &btnLongPressTask[event->Side]);

			// Setup and handle DOUBLE presses
#if ENABLE_DOUBLE_PRESS
			withinDoublePressTime[event->Side] = true;
			if (Scheduler_FindTask(&scheduler, TASK_BTN_DOUBLE_PRESS + event->Side) == &btnDoublePressTask[event->Side])
				Scheduler_Refresh(&scheduler, &btnDoublePressTask[event->Side]);
			else
				Scheduler_CreateSingleTask(&scheduler, &btnDoublePressTask[event->Side], TASK_BTN_DOUBLE_PRESS + event->Side, btnDoublePress_TaskHandler, &sides[event->Side], BUTTON_DOUBLE_PRESS);
#endif
			break;
	}
}

static void btnLongPress_TaskHandler(void* data) { Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, data); }

#if ENABLE_DOUBLE_PRESS
static void btnDoublePress_TaskHandler(void* data)
{
	EventSide* doublePressedButton              = data;
	withinDoublePressTime[*doublePressedButton] = false;
}
#endif

void Trigger_Setup() { Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler); }
