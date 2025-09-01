#include "stm32c0xx_hal.h"
#include "utilities.h"

Scheduler scheduler;

void Scheduler_Setup() { Scheduler_Init(&scheduler, HAL_GetTick); }
