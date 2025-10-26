#include "buzzer.h"
#include "cmdList.h"

#include <getopt.h>
#include <stdlib.h>

void buzzer_Cmd(const CLI* cli, const size_t argc, char* const argv[])
{
	enum
	{
		cmdVolume,
		cmdFrequency,
		cmdBuzz,
		cmdUnknown
	} cmd = cmdUnknown;

	uint8_t value;
	int     c;
	optind = 1; // Reset getopt index
	while ((c = getopt(argc, argv, "v:f:b")) != -1)
	{
		switch (c)
		{
			case 'v':
				cmd   = cmdVolume;
				value = (uint8_t)strtol(optarg, NULL, 10);
				break;
			case 'f':
				cmd   = cmdFrequency;
				value = (uint8_t)strtol(optarg, NULL, 10);
				break;
			case 'b':
				cmd = cmdBuzz;
				break;

			default:
				cmd = cmdUnknown;
				break;
		}
	}

	switch (cmd)
	{
		case cmdVolume:
			CLI_Write(cli, "Setting volume to %d\n", value);
			Buzzer_SetVolume(value);
			break;

		case cmdFrequency:
			CLI_Write(cli, "Selecting frequency %d\n", value);
			Buzzer_SetFreq(value);
			break;

		case cmdBuzz:
			CLI_Write(cli, "Buzzing!\n");
			Buzzer_Buzz();
			break;

		case cmdUnknown:
			CLI_Write(cli, "Unknown parameters\n");
			break;
	}
}

const char* const buzzer_Help[] = {0};
