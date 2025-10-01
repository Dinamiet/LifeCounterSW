#include "setting.h"

#include "battery.h"
#include "buzzer.h"
#include "config.h"
#include "display.h"
#include "utilities.h"

#include <stdint.h>

typedef struct _SettingOption_
{
	uint8_t (*GetSetting)(void);
	void (*SetSetting)(uint8_t);
	void (*Display)(EventSide side, uint16_t value);
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
		{.GetSetting = Display_GetBrightness, .SetSetting = Display_SetBrightness, .Display = Display_ShowUInt, .Value = 0},
		{     .GetSetting = Buzzer_GetVolume,      .SetSetting = Buzzer_SetVolume, .Display = Display_ShowUInt, .Value = 0},
		{       .GetSetting = Buzzer_GetFreq,        .SetSetting = Buzzer_SetFreq, .Display = Display_ShowUInt, .Value = 0},
		{   .GetSetting = Battery_GetSetting,    .SetSetting = Battery_SetSetting, .Display = Battery_ShowInfo, .Value = 0},
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

	SettingOption* selectedOption = &setting[side].Options[shown];
	selectedOption->Value         = selectedOption->GetSetting();
	selectedOption->Display(side, selectedOption->Value);
}

static void changeSetting_Handler(const void* data)
{
	EventData* event = (EventData*)data;

	if (!setting[event->Side].Active)
		return;

	uint8_t shown = setting[event->Side].CurrentShown;
	SettingOption* selectedOption = &setting[event->Side].Options[shown];
	switch (event->Increasing)
	{
		case true:
			if (selectedOption->Value < UINT16_MAX)
				++selectedOption->Value;
			break;

		case false:
			if (selectedOption->Value > 0)
				--selectedOption->Value;
			break;
	}

	selectedOption->SetSetting(selectedOption->Value);
	selectedOption->Display(event->Side, selectedOption->Value);
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
		SettingOption* selectedOption = &setting[side].Options[setting[side].CurrentShown];
		selectedOption->Value         = selectedOption->GetSetting();

		Display_ShowStatus(side, ~(1 << setting[side].CurrentShown));
		selectedOption->Display(side, selectedOption->Value);
	}
	else
	{
		Config_Save();
	}
}
