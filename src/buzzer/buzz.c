#include "buzzer.h"
#include "buzz.h"

#include "tim.h"

#include "utilities.h"
#include "tasks.h"

SchedulerTask buzzingOffTask;

void buzzingOff_Task(void* _);

void buzzingOff_Task(void* _)
{
	(void)_; // Unused

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
}

void buzzerBuzz(const void* _)
{
	(void)_; // Unused

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	if (Scheduler_FindTask(&scheduler, TASK_BUZZER_OFF))
		Scheduler_Refresh(&scheduler, &buzzingOffTask);
	else
		Scheduler_CreateSingleTask(&scheduler, &buzzingOffTask, TASK_BUZZER_OFF, buzzingOff_Task, NULL, BUZZ_ON_TIME);
}
