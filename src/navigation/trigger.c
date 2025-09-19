#include "trigger.h"

#include "events.h"
#include "tasks.h"
#include "utilities.h"

static ObserverSubscription btnEventNotifier;
static SchedulerTask btnDoublePressTask[EVENTSIDE_MAX];
static SchedulerTask btnLongPressTask[EVENTSIDE_MAX];

static EventSide sides[EVENTSIDE_MAX] = {EVENTSIDE_1, EVENTSIDE_2};
static bool withinDoublePressTime[EVENTSIDE_MAX] = {false};

static void btnEvent_Handler(const void* data);
static void btnLongPress_TaskHandler(void* data);
static void btnDoublePress_TaskHandler(void* data);

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
			if (withinDoublePressTime[event->Side])
			{
				withinDoublePressTime[event->Side] = false; // Reset the flag
				Scheduler_Remove(&scheduler, &btnDoublePressTask[event->Side]);
				Observer_Publish(&eventNotifier, EVENT_BUTTON_DOUBLE_PRESS, &event->Side);
			}
			else
				Observer_Publish(&eventNotifier, EVENT_BUTTON_SINGLE_PRESS, &event->Side);
			break;

		case false:
			// Setup and handle LONG presses
			if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Side) == &btnLongPressTask[event->Side])
				Scheduler_Remove(&scheduler, &btnLongPressTask[event->Side]);

			// Setup and handle DOUBLE presses
			withinDoublePressTime[event->Side] = true;
			if (Scheduler_FindTask(&scheduler, TASK_BTN_DOUBLE_PRESS + event->Side) == &btnDoublePressTask[event->Side])
				Scheduler_Refresh(&scheduler, &btnDoublePressTask[event->Side]);
			else
				Scheduler_CreateSingleTask(&scheduler, &btnDoublePressTask[event->Side], TASK_BTN_DOUBLE_PRESS + event->Side, btnDoublePress_TaskHandler, &sides[event->Side], BUTTON_DOUBLE_PRESS);
			break;
	}
}

static void btnLongPress_TaskHandler(void* data) { Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, data); }

static void btnDoublePress_TaskHandler(void* data)
{
	EventSide* doublePressedButton              = data;
	withinDoublePressTime[*doublePressedButton] = false;
}

void Trigger_Setup() { Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler); }
