#include "gpio.h"
#include "main.h"
#include "tasks.h"
#include "utilities.h"

SchedulerTask heartbeatTask;

static void heartbeat_Task(void* data);

static void heartbeat_Task(void* data)
{
	(void)data; // Unused
	HAL_GPIO_TogglePin(Heartbeat_GPIO_Port, Heartbeat_Pin);
}

void Heartbeat_Setup() { Scheduler_CreateRecurringTask(&scheduler, &heartbeatTask, TASK_HEARTBEAT, heartbeat_Task, NULL, HEARTBEAT_PERIOD); }
