#ifndef _TASKS_H_
#define _TASKS_H_

typedef enum _TaskID_
{
	TASK_HEARTBEAT,
	TASK_RENDER,
	TASK_BUTTON_MONITOR,
	TASK_KNOB_TURN,
	TASK_BUZZER_OFF,
	TASK_LONG_PRESS_CHECK,
	TASK_CLI,
} TaskID;

#define HEARTBEAT_PERIOD       500  // ms
#define RENDER_PERIOD          2    // ms
#define BUTTON_MONITOR_PERIOD  5    // ms
#define KNOB_TURN_PERIOD       5    // ms
#define BUZZ_ON_TIME           25   // ms
#define BUTTON_LONG_PRESS_TIME 500 // ms
#define CLI_PERIOD             50  // ms

#endif
