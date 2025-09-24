#include "cmdList.h"
#include "display.h"

#include <getopt.h>
#include <stdlib.h>

void display_Cmd(const CLI* cli, const size_t argc, char* const argv[])
{
	enum
	{
		cmdBrightness,
		cmdClear,
		cmdUnknown
	} cmd = cmdUnknown;

	uint8_t value;
	int     c;
	optind = 1; // Reset getopt index
	while ((c = getopt(argc, argv, "b:c:")) != -1)
	{
		switch (c)
		{
			case 'b':
				cmd   = cmdBrightness;
				value = (uint8_t)strtol(optarg, NULL, 10);
				break;

			case 'c':
				cmd   = cmdClear;
				value = (uint8_t)strtol(optarg, NULL, 10);
				break;

			default:
				cmd = cmdUnknown;
				break;
		}
	}

	switch (cmd)
	{
		case cmdBrightness:
			CLI_Write(cli, "Setting brightness to %d\n", value);
			Display_SetBrightness(value);
			break;

		case cmdClear:
			CLI_Write(cli, "Clearing display %d\n", value);
			Display_Clear(value);
			break;

		case cmdUnknown:
			CLI_Write(cli, "Unknown parameters\n");
			break;
	}
}

const char* const display_Help[] = {
		"Display settings and adjustments",
		"Usage: display -[b:c:]",
		" -b {value}  \tBrightness adjustment (0 - 100) ",
		" -c {display}\tClear display",
		0,
};
