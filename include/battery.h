#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "bq27441.h"
#include "events.h"

#include <stdint.h>

#define DEFAULT_CAPACITY          3350
#define DEFAULT_TERMINATE_VOLTAGE 2700
#define DEFAULT_TAPER_CURRENT     35
#define DEFAULT_SOC_THRESHOLD     15

extern BQ27441 batteryFuelGauge;

void Battery_Setup();
uint8_t Battery_EnterSetting(EventSide side);
void    Battery_ChangeSetting(EventSide side, uint8_t setting);
void    Battery_ShowInfo(EventSide side, uint16_t value);
void    Battery_ExitSetting(EventSide side);

#endif
