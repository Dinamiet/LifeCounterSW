#include "config.h"
#include "layout.h"

#include "display.h"
#include "buzzer.h"

void Config_Load()
{
	SettingStorage* storage = (SettingStorage*)SETTING_ADDRESS;

	Display_SetBrightness(storage->DisplayBrightness);
	Buzzer_SetVolume(storage->BuzzerVolume);
	Buzzer_SetFreq(storage->BuzzerFreq);
}
