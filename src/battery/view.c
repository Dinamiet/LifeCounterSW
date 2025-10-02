#include "battery.h"
#include "display.h"
#include "tasks.h"
#include "utilities.h"

typedef enum _BatteryParameterIndex_
{
	BATTERY_SOC,
	BATTERY_VOLTAGE,
	BATTERY_CURRENT,
	BATTERY_POWER,
	BATTERY_REMAINING_CAPACITY,
	BATTERY_FULL_CAPACITY,
	BATTERY_SOH,
	BATTERY_TEMPERATURE,
	BATTERY_MAX_PARAMS
} BatteryParameterIndex;

typedef struct _BatteryView_
{
	bool    PollingActive;
	uint8_t ViewParameter;
} BatteryView;

typedef struct _BatteryData_
{
	uint8_t  SOC;
	uint8_t  SOH;
	uint16_t Voltage;
	int16_t  Current;
	int16_t  Power;
	uint16_t RemainingCapacity;
	uint16_t FullCapacity;
	uint16_t Temperature;
} BatteryData;

static BatteryView   view[EVENTSIDE_MAX];
static BatteryData   data;
static SchedulerTask batteryDataPolling;

static void startPolling(EventSide side);
static void stopPolling(EventSide side);
static void battery_pollData(void* _);

static void startPolling(EventSide side)
{
	view[side].PollingActive = true;
	Scheduler_Activate(&batteryDataPolling);
}

static void stopPolling(EventSide side)
{
	view[side].PollingActive = false;

	bool anyRunning = false;
	for (EventSide i = 0; i < EVENTSIDE_MAX; i++) { anyRunning |= view[i].PollingActive; }

	if (!anyRunning)
		Scheduler_Deactivate(&batteryDataPolling);
}

static void battery_pollData(void* _)
{
	(void)_; // Unused

	static BatteryParameterIndex index = 0;

	for (EventSide side = 0; side < EVENTSIDE_MAX; side++)
	{
		if (view[side].PollingActive)
			Display_ShowDP(side, (index % 2) ? view[side].ViewParameter + 1 : 0);
	}

	switch (index)
	{
		case BATTERY_SOC:
			BQ27441_StateOfCharge(&batteryFuelGauge, &data.SOC);
			break;

		case BATTERY_VOLTAGE:
			BQ27441_Voltage(&batteryFuelGauge, &data.Voltage);
			break;

		case BATTERY_CURRENT:
			BQ27441_Current(&batteryFuelGauge, BQ27441_CURRENT_AVG, &data.Current);
			break;

		case BATTERY_POWER:
			BQ27441_Power(&batteryFuelGauge, &data.Power);
			break;

		case BATTERY_REMAINING_CAPACITY:
			BQ27441_Capacity(&batteryFuelGauge, BQ27441_CAPACITY_REMAINING_COMPENSATED, &data.RemainingCapacity);
			break;

		case BATTERY_FULL_CAPACITY:
			BQ27441_Capacity(&batteryFuelGauge, BQ27441_CAPACITY_FULL_COMPENSATED, &data.FullCapacity);
			break;

		case BATTERY_SOH:
			BQ27441_StateOfHealth(&batteryFuelGauge, BQ27441_STATEOFHEALTH_PERCENTAGE, &data.SOH);
			break;

		case BATTERY_TEMPERATURE:
			BQ27441_Temperature(&batteryFuelGauge, BQ27441_TEMPERATURE_INTERNAL, &data.Temperature);
			break;

		case BATTERY_MAX_PARAMS:
			break;
	}

	index = (index + 1) % BATTERY_MAX_PARAMS;

	for (EventSide i = 0; i < EVENTSIDE_MAX; i++)
	{
		if (view[i].PollingActive)
			Battery_ShowInfo(i, view[i].ViewParameter);
	}
}

uint8_t Battery_EnterSetting(EventSide side)
{
	Display_ShowDP(side, view[side].ViewParameter + 1);
	startPolling(side);
	return view[side].ViewParameter;
}

void Battery_ChangeSetting(EventSide side, uint8_t setting)
{
	view[side].ViewParameter = setting % BATTERY_MAX_PARAMS;
	Display_ShowDP(side, view[side].ViewParameter + 1);
}

void Battery_ShowInfo(EventSide side, uint16_t value)
{
	BatteryParameterIndex index = value % BATTERY_MAX_PARAMS;
	switch (index)
	{
		case BATTERY_SOC:
			Display_ShowUInt(side, data.SOC);
			break;

		case BATTERY_VOLTAGE:
			Display_ShowUInt(side, data.Voltage);
			break;

		case BATTERY_CURRENT:
			Display_ShowInt(side, data.Current);
			break;

		case BATTERY_POWER:
			Display_ShowInt(side, data.Power);
			break;

		case BATTERY_REMAINING_CAPACITY:
			Display_ShowInt(side, data.RemainingCapacity);
			break;

		case BATTERY_FULL_CAPACITY:
			Display_ShowInt(side, data.FullCapacity);
			break;

		case BATTERY_SOH:
			Display_ShowUInt(side, data.SOH);
			break;

		case BATTERY_TEMPERATURE:
			Display_ShowUInt(side, (data.Temperature/10)-273);
			break;

		case BATTERY_MAX_PARAMS:
			break;
	}
}

void    Battery_ExitSetting(EventSide side)
{
	Display_ShowDP(side, 0);
	stopPolling(side);
}

void battery_MonitoringSetup()
{
	Scheduler_CreateRecurringTask(&scheduler, &batteryDataPolling, TASK_BATTERY_POLLING, battery_pollData, NULL, BATTERY_POLL_PERIOD);
	Scheduler_Deactivate(&batteryDataPolling);
}
