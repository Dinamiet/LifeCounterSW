#include "button.h"
#include "encoder.h"
#include "knob.h"

void Encoder_Setup()
{
	Scheduler_CreateRecurringTask(&scheduler, &buttonMonitorTask, TASK_BUTTON_MONITOR, encoderBTNMonitor_Task, NULL, BUTTON_MONITOR_PERIOD);
	Scheduler_CreateRecurringTask(&scheduler, &knobTurnTask, TASK_KNOB_TURN, encoderKnobTurn_Task, NULL, KNOB_TURN_PERIOD);
}
