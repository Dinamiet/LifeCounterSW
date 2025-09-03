#ifndef _TASKS_H_
#define _TASKS_H_

typedef enum _TaskID_
{
	TASK_HEARTBEAT,
	TASK_RENDER,
	TASK_BUTTON_MONITOR,
} TaskID;

#define HEARTBEAT_PERIOD      500 // ms
#define RENDER_PERIOD         2   // ms
#define BUTTON_MONITOR_PERIOD 5   // ms

#endif
