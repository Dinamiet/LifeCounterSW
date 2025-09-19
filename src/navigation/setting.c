#include "setting.h"

#include "buzzer.h"
#include "display.h"
#include "utilities.h"

#include <stdint.h>

typedef struct _SettingOption_
{
	uint8_t (*GetSetting)(void);
	void (*SetSetting)(uint8_t);
	uint16_t Value;
} SettingOption;

typedef struct _Setting_
{
	bool           Active;
	uint8_t        CurrentShown;
	SettingOption* Options;
} Setting;

static ObserverSubscription settingSwitchWatcher;
static ObserverSubscription settingChangeWatcher;

static SettingOption settingOptions[MAX_SETTINGS] = {
		{.GetSetting = Display_GetBrightness, .SetSetting = Display_SetBrightness, .Value = 0},
		{     .GetSetting = Buzzer_GetVolume,      .SetSetting = Buzzer_SetVolume, .Value = 0},
		{       .GetSetting = Buzzer_GetFreq,        .SetSetting = Buzzer_SetFreq, .Value = 0},
};

static Setting setting[EVENTSIDE_MAX] = {
		{
         .Active       = false,
         .CurrentShown = 0,
         .Options      = settingOptions,
		 },
		{
         .Active       = false,
         .CurrentShown = 0,
         .Options      = settingOptions,
		 },
};

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

	setting[side].Options[shown].Value = setting[side].Options[shown].GetSetting();

	Display_ShowUInt(side, setting[side].Options[shown].Value);
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
			if (setting[event->Side].Options[shown].Value < UINT16_MAX)
				++setting[event->Side].Options[shown].Value;
			break;

		case false:
			if (setting[event->Side].Options[shown].Value > 0)
				--setting[event->Side].Options[shown].Value;
			break;
	}

	Display_ShowUInt(event->Side, setting[event->Side].Options[shown].Value);
	setting[event->Side].Options[shown].SetSetting(setting[event->Side].Options[shown].Value);
}

void Setting_Init()
{
	Observer_Subscribe(&eventNotifier, &settingSwitchWatcher, EVENT_BUTTON_SINGLE_PRESS, nextSetting_Handler);
	Observer_Subscribe(&eventNotifier, &settingChangeWatcher, EVENT_KNOB, changeSetting_Handler);
}

void Setting_Active(EventSide side, bool active)
{
	setting[side].Active = active;
	if (active)
	{
		setting[side].Options[setting[side].CurrentShown].Value = setting[side].Options[setting[side].CurrentShown].GetSetting();

		Display_ShowStatus(side, ~(1 << setting[side].CurrentShown));
		Display_ShowUInt(side, setting[side].Options[setting[side].CurrentShown].Value);
	}
}
