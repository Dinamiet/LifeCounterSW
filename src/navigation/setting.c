#include "setting.h"

#include "battery.h"
#include "buzzer.h"
#include "config.h"
#include "display.h"
#include "utilities.h"

#include <stdint.h>

#define MAX_SETTING_VALUE 100

typedef struct _SettingOption_
{
	uint8_t (*EnterSetting)(EventSide side);
	void (*ChangeSetting)(EventSide side, uint8_t value);
	void (*Display)(EventSide side, uint16_t value);
	void (*ExitSetting)(EventSide side);
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

static void nextSetting_Handler(const void* data);
static void changeSetting_Handler(const void* data);

static uint8_t getDisplayBrightness(EventSide _);
static uint8_t getBuzzerVolume(EventSide _);
static uint8_t getBuzzerFreq(EventSide _);
static void    setBrightness(EventSide _, uint8_t value);
static void    setBuzzerVolume(EventSide _, uint8_t value);
static void    setBuzzerFreq(EventSide _, uint8_t value);

static SettingOption settingOptions[MAX_SETTINGS] = {
		{.EnterSetting = getDisplayBrightness,         .ChangeSetting = setBrightness, .Display = Display_ShowUInt,                .ExitSetting = NULL, .Value = 0},
		{     .EnterSetting = getBuzzerVolume,       .ChangeSetting = setBuzzerVolume, .Display = Display_ShowUInt,                .ExitSetting = NULL, .Value = 0},
		{       .EnterSetting = getBuzzerFreq,         .ChangeSetting = setBuzzerFreq, .Display = Display_ShowUInt,                .ExitSetting = NULL, .Value = 0},
		{.EnterSetting = Battery_EnterSetting, .ChangeSetting = Battery_ChangeSetting, .Display = Battery_ShowInfo, .ExitSetting = Battery_ExitSetting, .Value = 0},
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

static void nextSetting_Handler(const void* data)
{
	EventSide side = *(EventSide*)data;

	if (!setting[side].Active)
		return;

	uint8_t current = setting[side].CurrentShown;
	if (setting[side].Options[current].ExitSetting)
		setting[side].Options[current].ExitSetting(side);

	uint8_t shown = (setting[side].CurrentShown + 1) % MAX_SETTINGS;

	setting[side].CurrentShown = shown;
	Display_ShowStatus(side, ~(1 << shown));

	SettingOption* selectedOption = &setting[side].Options[shown];
	selectedOption->Value         = selectedOption->EnterSetting(side);
	selectedOption->Display(side, selectedOption->Value);
}

static void changeSetting_Handler(const void* data)
{
	EventData* event = (EventData*)data;

	if (!setting[event->Side].Active)
		return;

	uint8_t        shown          = setting[event->Side].CurrentShown;
	SettingOption* selectedOption = &setting[event->Side].Options[shown];
	switch (event->Increasing)
	{
		case true:
			if (selectedOption->Value < MAX_SETTING_VALUE)
				++selectedOption->Value;
			break;

		case false:
			if (selectedOption->Value > 0)
				--selectedOption->Value;
			break;
	}

	selectedOption->ChangeSetting(event->Side, selectedOption->Value);
	selectedOption->Display(event->Side, selectedOption->Value);
}

static uint8_t getDisplayBrightness(EventSide _)
{
	(void)_; // Unused
	return Display_GetBrightness();
}

static uint8_t getBuzzerVolume(EventSide _)
{
	(void)_; // Unused
	return Buzzer_GetVolume();
}

static uint8_t getBuzzerFreq(EventSide _)
{
	(void)_; // Unused
	return Buzzer_GetFreq();
}

static void setBrightness(EventSide _, uint8_t value)
{
	(void)_; // Unused;
	Display_SetBrightness(value);
}

static void setBuzzerVolume(EventSide _, uint8_t value)
{
	(void)_; // Unused;
	Buzzer_SetVolume(value);
}

static void setBuzzerFreq(EventSide _, uint8_t value)
{
	(void)_; // Unused;
	Buzzer_SetFreq(value);
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
		selectedOption->Value         = selectedOption->EnterSetting(side);

		Display_ShowStatus(side, ~(1 << setting[side].CurrentShown));
		selectedOption->Display(side, selectedOption->Value);
	}
	else
	{
		if (setting[side].Options[setting[side].CurrentShown].ExitSetting)
			setting[side].Options[setting[side].CurrentShown].ExitSetting(side);
		Config_Save();
	}
}
