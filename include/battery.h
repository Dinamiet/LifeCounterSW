#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "bq27441.h"
#include "events.h"

#include <stdint.h>

#define DEFAULT_CAPACITY          3500
#define DEFAULT_TERMINATE_VOLTAGE 2400
#define DEFAULT_TAPER_CURRENT     30

extern BQ27441 batteryFuelGauge;

void Battery_Setup();

#endif
