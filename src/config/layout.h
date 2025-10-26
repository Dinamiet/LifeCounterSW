#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <stdint.h>

typedef union _SettingStorage_
{
	uint64_t Data;
	struct
	{
		uint8_t DisplayBrightness;
		uint8_t BuzzerVolume;
		uint8_t BuzzerFreq;
	};
} SettingStorage;

#define SETTING_ADDRESS 0x8007800

#endif
