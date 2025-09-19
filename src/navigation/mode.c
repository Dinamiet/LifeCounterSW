#include "mode.h"
#include "counter.h"
#include "setting.h"
#include "utilities.h"

static ObserverSubscription modeChangeWatcher;

static void modeChange_Handler(const void* data)
{
	static NavMode currentMode = MODE_COUNTER;
	EventSide side = *(EventSide*)data;

	currentMode = (currentMode + 1) % MODE_MAX;
	Mode_Change(side, currentMode);
}

void Mode_Setup()
{
	Observer_Subscribe(&eventNotifier, &modeChangeWatcher, EVENT_BUTTON_LONG_PRESS, modeChange_Handler);
}

void Mode_Change(EventSide side, NavMode mode)
{
	Counter_Active(side, mode == MODE_COUNTER);
	Setting_Active(side, mode == MODE_SETTING);
}
