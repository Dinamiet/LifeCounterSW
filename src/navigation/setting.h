#ifndef _SETTING_H_
#define _SETTING_H_

#include "events.h"

#define MAX_SETTINGS 4

void Setting_Init();
void Setting_Active(EventSide side, bool active);

#endif
