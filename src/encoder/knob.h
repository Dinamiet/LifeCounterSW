#ifndef _KNOB_H_
#define _KNOB_H_

#include "utilities.h"
#include "tasks.h"

extern SchedulerTask knobTurnTask;

void encoderKnobTurn_Task(void* _);

#endif
