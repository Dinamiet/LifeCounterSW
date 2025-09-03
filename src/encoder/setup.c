#include "encoder.h"
#include "button.h"

void Encoder_Setup()
{
	Scheduler_CreateRecurringTask(&scheduler, &buttonMonitorTask, TASK_BUTTON_MONITOR, encoderBTNMonitor_Task, NULL, BUTTON_MONITOR_PERIOD);
}
