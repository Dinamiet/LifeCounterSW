#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "events.h"

#define MAX_COUNTERS 4

void Counter_Init();
void Counter_Active(EventSide side, bool active);

#endif
