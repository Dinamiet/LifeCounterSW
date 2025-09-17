#include "trigger.h"

#include "events.h"
#include "tasks.h"
#include "utilities.h"

static ObserverSubscription btnEventNotifier;
static SchedulerTask        btnDoublePressTask[MAX_BUTTONS];
static SchedulerTask        btnLongPressTask[MAX_BUTTONS];

static Buttons button[MAX_BUTTONS]                = {BUTTON_1, BUTTON_2};
static bool    withinDoublePressTime[MAX_BUTTONS] = {false};

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
			if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Button) == &btnLongPressTask[event->Button])
				Scheduler_Refresh(&scheduler, &btnLongPressTask[event->Button]);
			else
				Scheduler_CreateSingleTask(&scheduler, &btnLongPressTask[event->Button], TASK_BTN_LONG_PRESS + event->Button, btnLongPress_TaskHandler, &button[event->Button], BUTTON_LONG_PRESS);

			// Setup and handle DOUBLE presses
			if (withinDoublePressTime[event->Button])
			{
				withinDoublePressTime[event->Button] = false; // Reset the flag
				Scheduler_Remove(&scheduler, &btnDoublePressTask[event->Button]);
				Observer_Publish(&eventNotifier, EVENT_BUTTON_DOUBLE_PRESS, &event->Button);
			}
			else
				Observer_Publish(&eventNotifier, EVENT_BUTTON_SINGLE_PRESS, &event->Button);
			break;

		case false:
			// Setup and handle LONG presses
			if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Button) == &btnLongPressTask[event->Button])
				Scheduler_Remove(&scheduler, &btnLongPressTask[event->Button]);

			// Setup and handle DOUBLE presses
			withinDoublePressTime[event->Button] = true;
			if (Scheduler_FindTask(&scheduler, TASK_BTN_DOUBLE_PRESS + event->Button) == &btnDoublePressTask[event->Button])
				Scheduler_Refresh(&scheduler, &btnDoublePressTask[event->Button]);
			else
				Scheduler_CreateSingleTask(&scheduler, &btnDoublePressTask[event->Button], TASK_BTN_DOUBLE_PRESS + event->Button, btnDoublePress_TaskHandler, &button[event->Button], BUTTON_DOUBLE_PRESS);
			break;
	}
}

static void btnLongPress_TaskHandler(void* data) { Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, data); }

static void btnDoublePress_TaskHandler(void* data)
{
	Buttons* doublePressedButton                = data;
	withinDoublePressTime[*doublePressedButton] = false;
}

void Trigger_Setup() { Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler); }
