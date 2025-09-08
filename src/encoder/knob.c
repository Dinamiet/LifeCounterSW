#include "knob.h"

#include "events.h"
#include "gpio.h"
#include "main.h"

#include <stdint.h>

SchedulerTask knobTurnTask;

int8_t knob1PendingSteps = 0;
int8_t knob2PendingSteps = 0;

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
		case Encoder1CLK_Pin:
			if (HAL_GPIO_ReadPin(Encoder1DAT_GPIO_Port, Encoder1DAT_Pin))
				++knob1PendingSteps;
			else
				--knob1PendingSteps;
			break;

		case Encoder2CLK_Pin:
			if (HAL_GPIO_ReadPin(Encoder2DAT_GPIO_Port, Encoder2DAT_Pin))
				--knob2PendingSteps;
			else
				++knob2PendingSteps;
	}
}

void encoderKnobTurn_Task(void* _)
{
	(void)_; // Unused

	if (knob1PendingSteps > 0)
	{
		Observer_Publish(&eventNotifier, EVENT_KNOB_1_INC, NULL);
		--knob1PendingSteps;
	}
	else if (knob1PendingSteps < 0)
	{
		Observer_Publish(&eventNotifier, EVENT_KNOB_1_DEC, NULL);
		++knob1PendingSteps;
	}

	if (knob2PendingSteps > 0)
	{
		Observer_Publish(&eventNotifier, EVENT_KNOB_2_INC, NULL);
		--knob2PendingSteps;
	}
	else if (knob2PendingSteps < 0)
	{
		Observer_Publish(&eventNotifier, EVENT_KNOB_2_DEC, NULL);
		++knob2PendingSteps;
	}
}
