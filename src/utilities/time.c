#include "stm32c0xx_hal.h"
#include "utilities.h"

uint32_t Utilities_GetTime() { return HAL_GetTick(); }
