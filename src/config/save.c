#include "config.h"
#include "layout.h"
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_flash.h"

#include "display.h"
#include "buzzer.h"

void Config_Save()
{
	SettingStorage newSettings = {
	    .DisplayBrightness = Display_GetBrightness(),
	    .BuzzerVolume = Buzzer_GetVolume(),
	    .BuzzerFreq = Buzzer_GetFreq()
	};

	FLASH_EraseInitTypeDef eraseInfo = {
		.TypeErase = FLASH_TYPEERASE_PAGES,
		.Page = (SETTING_ADDRESS - FLASH_BASE) / FLASH_PAGE_SIZE,
		.NbPages = 1,
	};

	uint32_t pageError;

	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase(&eraseInfo, &pageError);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, SETTING_ADDRESS, newSettings.Data);

	HAL_FLASH_Lock();
}
