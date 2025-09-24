// clang-format off
#include "gpio.h"
// clang-format on
#include "cmdList.h"

void poweroff_Cmd(const CLI* cli, const size_t argc, const char* const argv[])
{
	(void)argc; // Unused
	(void)argv; // Unused

	CLI_Write(cli, "Powering off...\r\n");
	HAL_GPIO_WritePin(PWR_Ctrl_GPIO_Port, PWR_Ctrl_Pin, GPIO_PIN_RESET);
}

const char* const poweroff_Help[] = {
		"Usage: poweroff",
		"Power off the device",
		0,
};
