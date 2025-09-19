#include "heartbeat.h"

#include "gpio.h"

SchedulerTask heartbeatTask;

void heartbeat_Task(void* data)
{
	(void)data; // Unused
	HAL_GPIO_TogglePin(Heartbeat_GPIO_Port, Heartbeat_Pin);
}
