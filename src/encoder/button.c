#include "button.h"

#include "events.h"
#include "utilities.h"

SchedulerTask buttonMonitorTask;

void encoderBTNMonitor_Task(void* _)
{
	(void)_; // Unused
	static bool btn1PrevState = false;
	static bool btn2PrevState = false;

	bool btn1State = HAL_GPIO_ReadPin(Encoder1BTN_GPIO_Port, Encoder1BTN_Pin);
	bool btn2State = HAL_GPIO_ReadPin(Encoder2BTN_GPIO_Port, Encoder2BTN_Pin);

	if (btn1PrevState != btn1State)
	{
		EventData data = {.Side = EVENTSIDE_1, .State = btn1State};
		Observer_Publish(&eventNotifier, EVENT_BUTTON, &data);
	}

	if (btn2PrevState != btn2State)
	{
		EventData data = {.Side = EVENTSIDE_2, .State = btn2State};
		Observer_Publish(&eventNotifier, EVENT_BUTTON, &data);
	}

	btn1PrevState = btn1State;
	btn2PrevState = btn2State;
}
