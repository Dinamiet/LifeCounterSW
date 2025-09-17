#include "navigation.h"

#include "utilities.h"
#include "events.h"
#include "tasks.h"

static ObserverSubscription btnEventNotifier;
static SchedulerTask btnDoublePressTask[MAX_BUTTONS];
static SchedulerTask btnLongPressTask[MAX_BUTTONS];

static Buttons button[MAX_BUTTONS] = {BUTTON_1, BUTTON_2};
static bool withinDoublePressTime[MAX_BUTTONS]= {false};

static void btnEvent_Handler(const void* _data);
static void btnLongPress_Handler(void* _);
static void btnDoublePress_Handler(void* _data);

static void btnEvent_Handler(const void* _data)
{
	const EventData* event = _data;

	switch (event->State)
	{
	case true:
		// Setup and handle LONG presses
		if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Button) == &btnLongPressTask[event->Button])
			Scheduler_Refresh(&scheduler, &btnLongPressTask[event->Button]);
		else
			Scheduler_CreateSingleTask(&scheduler, &btnLongPressTask[event->Button], TASK_BTN_LONG_PRESS + event->Button, btnLongPress_Handler, &button[event->Button], BUTTON_LONG_PRESS);

		// Setup and handle DOUBLE presses
		if (withinDoublePressTime[event->Button])
		{
			withinDoublePressTime[event->Button] = false; // Reset the flag
			Scheduler_Remove(&scheduler, &btnDoublePressTask[event->Button]);
			Observer_Publish(&eventNotifier, EVENT_BUTTON_DOUBLE_PRESS, &event->Button);
		}
		break;

	case false:
		// Setup and handle LONG presses
		if (Scheduler_FindTask(&scheduler, TASK_BTN_LONG_PRESS + event->Button) == &btnLongPressTask[event->Button])
			Scheduler_Remove(&scheduler, &btnLongPressTask[event->Button]);

		// Setup and handle DOUBLE presses
		withinDoublePressTime[event->Button] = true;
		if (Scheduler_FindTask(&scheduler, TASK_BTN_2_DOUBLE_PRESS + event->Button) == &btnDoublePressTask[event->Button])
			Scheduler_Refresh(&scheduler, &btnDoublePressTask[event->Button]);
		else
			Scheduler_CreateSingleTask(&scheduler, &btnDoublePressTask[event->Button], TASK_BTN_DOUBLE_PRESS + event->Button, btnDoublePress_Handler, &button[event->Button], BUTTON_DOUBLE_PRESS);
		break;
	}
}

static void btnLongPress_Handler(void* data)
{
	Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, data);
}

static void btnDoublePress_Handler(void* data)
{
	Buttons* doublePressedButton = data;
	withinDoublePressTime[*doublePressedButton] = false;
}

void Navigation_Setup()
{
	Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler);
}
