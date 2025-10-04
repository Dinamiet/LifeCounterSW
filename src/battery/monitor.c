#include "battery.h"
#include "display.h"
#include "events.h"
#include "gpio.h"
#include "string.h"
#include "tasks.h"
#include "utilities.h"

typedef enum _MonitorState_
{
	MONITOR_RESET_CHECK,
	MONITOR_SEALED,
	MONITOR_UNSEAL,
	MONITOR_ENTER_CONFIG_MODE,
	MONITOR_WAIT_CONFIG_MODE,
	MONITOR_CONFIGURE_BATTERY,
	MONITOR_CONFIGURE_GPIO_MODE,
	MONITOR_CONFIGURE_GPIO_POLARITY,
	MONITOR_SOFT_RESET,
	MONITOR_BAT_LOW_START,
	MONITOR_BAT_LOW_CHECK,
} MonitorState;

SchedulerTask batteryMonitorTask;

static void battery_ShowStatus(bool busy);
static void battery_MonitorTask(void* _);

static void battery_ShowStatus(bool busy)
{
	for (EventSide side = 0; side < EVENTSIDE_MAX; side++) { Display_ShowDP(side, busy ? 0xFF : 0x00); }
}

static void battery_MonitorTask(void* _)
{
	(void)_; // Unused

	static MonitorState state = MONITOR_RESET_CHECK;

	BQ27441Flags  flags;
	BQ27441Status status;

	switch (state)
	{
		case MONITOR_RESET_CHECK:
			battery_ShowStatus(true);
			if (BQ27441_Flags(&batteryFuelGauge, &flags))
				state = flags.ResetOccured ? MONITOR_SEALED : MONITOR_BAT_LOW_START;
			break;

		case MONITOR_SEALED:
			if (BQ27441_Status(&batteryFuelGauge, &status))
				state = status.Sealed ? MONITOR_UNSEAL : MONITOR_ENTER_CONFIG_MODE;
			break;

		case MONITOR_UNSEAL:
			if (BQ27441_Unseal(&batteryFuelGauge))
				state = MONITOR_ENTER_CONFIG_MODE;
			break;

		case MONITOR_ENTER_CONFIG_MODE:
			if (BQ27441_EnterMode(&batteryFuelGauge, BQ27441_MODE_CONFIGURE))
				state = MONITOR_WAIT_CONFIG_MODE;
			break;

		case MONITOR_WAIT_CONFIG_MODE:
			if (BQ27441_Flags(&batteryFuelGauge, &flags))
				state = flags.ConfigUpdateMode ? MONITOR_CONFIGURE_BATTERY : state;
			break;

		case MONITOR_CONFIGURE_BATTERY:
			if (BQ27441_Configure(&batteryFuelGauge, DEFAULT_CAPACITY, DEFAULT_TERMINATE_VOLTAGE, DEFAULT_TAPER_CURRENT))
				state = MONITOR_CONFIGURE_GPIO_MODE;
			break;

		case MONITOR_CONFIGURE_GPIO_MODE:
			if (BQ27441_SetGPOUTMode(&batteryFuelGauge, BQ27441_GPOUT_BAT_LOW))
				state = MONITOR_CONFIGURE_GPIO_POLARITY;
			break;

		case MONITOR_CONFIGURE_GPIO_POLARITY:
			if (BQ27441_SetGPOUTPolarity(&batteryFuelGauge, BQ27441_GPOUT_POLARITY_ACTIVE_LOW))
				state = MONITOR_SOFT_RESET;
			break;

		case MONITOR_SOFT_RESET:
			if (BQ27441_SoftReset(&batteryFuelGauge))
				state = MONITOR_RESET_CHECK;
			break;

		case MONITOR_BAT_LOW_START:
			battery_ShowStatus(false);
			Scheduler_ChangePeriod(&batteryMonitorTask, BATTERY_MONITOR_PERIOD);
			state = MONITOR_BAT_LOW_CHECK;
			break;

		case MONITOR_BAT_LOW_CHECK:
			if (HAL_GPIO_ReadPin(PWR_OK_GPIO_Port, PWR_OK_Pin) == GPIO_PIN_RESET && BQ27441_Flags(&batteryFuelGauge, &flags))
			{
				if (flags.Discharging)
				{
					Scheduler_ChangePeriod(&batteryMonitorTask, BATTERY_MONITOR_PERIOD_START);
					Observer_Publish(&eventNotifier, EVENT_BEEP, NULL);
				}
				else
				{
					Scheduler_ChangePeriod(&batteryMonitorTask, BATTERY_MONITOR_PERIOD);
				}
			}
			break;
	}
}

void battery_MonitorSetup() { Scheduler_CreateRecurringTask(&scheduler, &batteryMonitorTask, TASK_BATTERY_MONITOR, battery_MonitorTask, NULL, BATTERY_MONITOR_PERIOD_START); }
