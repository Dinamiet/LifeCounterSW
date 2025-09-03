#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "observer.h"
#include "scheduler.h"

extern Scheduler scheduler;
extern Observer  eventNotifier;

void Utilities_Setup();

#endif
