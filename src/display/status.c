#include "display.h"
#include "render.h"

void Display_ShowStatus(EventSide side, uint8_t status) { display[side].Status = status; }
