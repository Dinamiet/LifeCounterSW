#include "button.h"

SchedulerTask buttonMonitorTask;

void encoderBTNMonitor_Task(void* _)
{
	(void)_; // Unused
	static bool    btn1PrevState = false;
	static bool    btn2PrevState = false;

	bool btn1State = HAL_GPIO_ReadPin(Encoder1BTN_GPIO_Port, Encoder1BTN_Pin);
	bool btn2State = HAL_GPIO_ReadPin(Encoder2BTN_GPIO_Port, Encoder2BTN_Pin);

	if (btn1PrevState != btn1State)
	{
		/** TODO: Handle button state changed */
	}

	if (btn2PrevState != btn2State)
	{
		/** TODO: Handle button state changed */
	}

	btn1PrevState = btn1State;
	btn2PrevState = btn2State;
}
