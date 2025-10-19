// clang-format off
#include "i2c.h"
// clang-format on
#include "battery.h"
#include "cmdList.h"

#include <getopt.h>

#define FUEL_GAUGE_ADDRESS 0x55

void battery_Cmd(const CLI* cli, const size_t argc, char* const argv[])
{
	enum
	{
		cmdSOC,
		cmdTemp,
		cmdCurrent,
		cmdUnknown,
		cmdCapacity,
	} cmd = cmdUnknown;

	int      c;
	uint16_t value;
	int16_t  signedValue;
	uint8_t  smallValue;
	optind = 1; // Reset getopt index
	while ((c = getopt(argc, argv, "stic")) != -1)
	{
		switch (c)
		{
			case 's':
				cmd = cmdSOC;
				break;

			case 't':
				cmd = cmdTemp;
				break;

			case 'i':
				cmd = cmdCurrent;
				break;

			case 'c':
				cmd = cmdCapacity;
				break;

			default:
				cmd = cmdUnknown;
				break;
		}
	}

	switch (cmd)
	{
		case cmdSOC:
			BQ27441_StateOfCharge(&batteryFuelGauge, &smallValue);
			CLI_Write(cli, "SOC: %X%%\n", value);
			break;

		case cmdTemp:
			BQ27441_Temperature(&batteryFuelGauge, BQ27441_TEMPERATURE_BATTERY, &value);
			CLI_Write(cli, "Temp: %dC\n", value / 10 - 275);
			break;

		case cmdCurrent:
			BQ27441_Current(&batteryFuelGauge, BQ27441_CURRENT_AVG, &signedValue);
			CLI_Write(cli, "Current: %dmA\n", (int16_t)value);
			break;

		case cmdCapacity:
			BQ27441_Capacity(&batteryFuelGauge, BQ27441_CAPACITY_REMAINING_COMPENSATED, &value);
			CLI_Write(cli, "Capacity: %dmAh\n", value);
			break;

		case cmdUnknown:
			CLI_Write(cli, "Unknown parameters\n");
			break;
	}
}

const char* const battery_Help[] = {0};
