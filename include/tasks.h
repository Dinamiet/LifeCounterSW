#ifndef _TASKS_H_
#define _TASKS_H_

typedef enum _TaskID_
{
	TASK_HEARTBEAT,
	TASK_RENDER,
} TaskID;

#define HEARTBEAT_PERIOD 500 // ms
#define RENDER_PERIOD 1 // ms

#endif
