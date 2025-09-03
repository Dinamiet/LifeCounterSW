#include "heartbeat.h"
#include "stm32c0xx_hal.h"
#include "tasks.h"
#include "utilities.h"

Scheduler scheduler;
Observer  eventNotifier;

void Utilities_Setup()
{
	Scheduler_Init(&scheduler, HAL_GetTick);
	Observer_Init(&eventNotifier);

	Scheduler_CreateRecurringTask(&scheduler, &heartbeatTask, TASK_HEARTBEAT, heartbeat_Task, NULL, HEARTBEAT_PERIOD);
}
