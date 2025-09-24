#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <stdint.h>

void     Battery_Setup();
uint16_t Battery_Temperature();
uint16_t Battery_SOC();
int16_t  Battery_Current();
uint16_t Battery_Capacity();

#endif
