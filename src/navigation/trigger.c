#include "trigger.h"

#include "buzzer.h"
#include "events.h"
#include "tasks.h"
#include "utilities.h"

static ObserverSubscription btnEventNotifier;
static SchedulerTask        longPressCheckTask;

static uint32_t btnDownTime[EVENTSIDE_MAX];

static void btnEvent_Handler(const void* data);
static void longPressCheck_Task(void* _);

static void btnEvent_Handler(const void* data)
{
	const EventData* event = data;

	uint32_t now      = Utilities_GetTime();
	uint32_t downTime = now - btnDownTime[event->Side];
	bool     allReleased = true;

	switch (event->State)
	{
		case true:
			btnDownTime[event->Side] = now;
			if (!Scheduler_FindTask(&scheduler, TASK_LONG_PRESS_CHECK))
				Scheduler_CreateRecurringTask(&scheduler, &longPressCheckTask, TASK_LONG_PRESS_CHECK, longPressCheck_Task, NULL, BUTTON_LONG_PRESS_TIME);
			break;

		case false:
			btnDownTime[event->Side] = 0;
			for (EventSide i = 0; i < EVENTSIDE_MAX; i++) allReleased &= btnDownTime[i] == 0;
			if (allReleased)
				Scheduler_Remove(&scheduler, &longPressCheckTask);

			if (downTime < BUTTON_LONG_PRESS_TIME)
				Observer_Publish(&eventNotifier, EVENT_BUTTON_SINGLE_PRESS, &event->Side);
			else if (downTime < (2 * BUTTON_LONG_PRESS_TIME))
				Observer_Publish(&eventNotifier, EVENT_BUTTON_LONG_PRESS, &event->Side);
			else
				Observer_Publish(&eventNotifier, EVENT_BUTTON_EXTRA_LONG_PRESS, &event->Side);
			break;
	}
}

static void longPressCheck_Task(void* _)
{
	(void)_; // Unused

	Buzzer_Buzz();
}

void Trigger_Setup() { Observer_Subscribe(&eventNotifier, &btnEventNotifier, EVENT_BUTTON, btnEvent_Handler); }
