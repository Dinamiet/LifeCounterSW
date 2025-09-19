#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "gpio.h"
#include "tasks.h"
#include "utilities.h"

extern SchedulerTask buttonMonitorTask;

void encoderBTNMonitor_Task(void* _);

#endif
