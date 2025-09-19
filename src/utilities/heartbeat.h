#ifndef _HEARTBEAT_H_
#define _HEARTBEAT_H_

#include "utilities.h"

extern SchedulerTask heartbeatTask;
void heartbeat_Task(void* data);

#endif
