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
			value = Battery_SOC();
			CLI_Write(cli, "SOC: %X%%\n", value);
			break;

		case cmdTemp:
			value = Battery_Temperature();
			CLI_Write(cli, "Temp: %dC\n", value);
			break;

		case cmdCurrent:
			value = Battery_Current();
			CLI_Write(cli, "Current: %dmA\n", (int16_t)value);
			break;

		case cmdCapacity:
			value = Battery_Capacity();
			CLI_Write(cli, "Capacity: %dmAh\n", value);
			break;

		case cmdUnknown:
			CLI_Write(cli, "Unknown parameters\n");
			break;
	}
}

const char* const battery_Help[] = {0};
