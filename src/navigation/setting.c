#include "setting.h"

#include "display.h"
#include "utilities.h"

#include <stdint.h>

typedef struct _Setting_
{
	bool     Active;
	uint8_t  CurrentShown;
	uint16_t Values[MAX_SETTINGS];
} Setting;

static ObserverSubscription settingSwitchWatcher;
static ObserverSubscription settingChangeWatcher;

static Setting setting[EVENTSIDE_MAX];

static void nextSetting_Handler(const void* data);
static void changeSetting_Handler(const void* data);

static void nextSetting_Handler(const void* data)
{
	EventSide side = *(EventSide*)data;

	if (!setting[side].Active)
		return;

	uint8_t shown = (setting[side].CurrentShown + 1) % MAX_SETTINGS;

	setting[side].CurrentShown = shown;
	Display_ShowStatus(side, ~(1 << shown));
	Display_ShowUInt(side, setting[side].Values[shown]);
}

static void changeSetting_Handler(const void* data)
{
	EventData* event = (EventData*)data;

	if (!setting[event->Side].Active)
		return;

	uint8_t shown = setting[event->Side].CurrentShown;
	switch (event->Increasing)
	{
		case true:
			if (setting[event->Side].Values[shown] < UINT16_MAX)
				++setting[event->Side].Values[shown];
			break;

		case false:
			if (setting[event->Side].Values[shown] > 0)
				--setting[event->Side].Values[shown];
			break;
	}

	Display_ShowUInt(event->Side, setting[event->Side].Values[shown]);
}

void Setting_Init()
{
	for (EventSide side = 0; side < EVENTSIDE_MAX; ++side)
	{
		setting[side].Active       = false;
		setting[side].CurrentShown = 0;
		for (uint8_t i = 0; i < MAX_SETTINGS; ++i) setting[side].Values[i] = 1000;
	}

	Observer_Subscribe(&eventNotifier, &settingSwitchWatcher, EVENT_BUTTON_SINGLE_PRESS, nextSetting_Handler);
	Observer_Subscribe(&eventNotifier, &settingChangeWatcher, EVENT_KNOB, changeSetting_Handler);
}

void Setting_Active(EventSide side, bool active)
{
	setting[side].Active = active;
	if (active)
	{
		Display_ShowStatus(side, ~(1 << setting[side].CurrentShown));
		Display_ShowUInt(side, setting[side].Values[setting[side].CurrentShown]);
	}
}
