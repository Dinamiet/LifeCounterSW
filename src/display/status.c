#include "display.h"
#include "render.h"

void Display_ShowStatus(EventSide side, uint8_t status) { display[side].Status = status; }
void Display_ShowDP(EventSide side, uint8_t dp) { display[side].Point = dp; }
