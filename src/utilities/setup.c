#include "heartbeat.h"
#include "tasks.h"
#include "utilities.h"

Scheduler scheduler;
Observer  eventNotifier;

void Utilities_Setup()
{
	Scheduler_Init(&scheduler, Utilities_GetTime);
	Observer_Init(&eventNotifier);

	Scheduler_CreateRecurringTask(&scheduler, &heartbeatTask, TASK_HEARTBEAT, heartbeat_Task, NULL, HEARTBEAT_PERIOD);
}
