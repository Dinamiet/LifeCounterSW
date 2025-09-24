// clang-format off
#include "usart.h"
// clang-format on
#include "cmd.h"
#include "cmdList.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

#define PROMPT ">>"
#define CMD(x) {#x, x##_Cmd, x##_Help}

static CLI           cmdLine;
static SchedulerTask cliTask;
static size_t        cmdLine_read(char* str, size_t max);
static size_t        cmdLine_write(const char* format, va_list params);
static void          cliTask_Handler(void* data);

static CLICommand cmdList[] = {
		CMD(display),
		CMD(buzzer),
		CMD(poweroff),
		{"help", CLI_Cmd, CLI_Help},
		{  NULL,    NULL,     NULL}
};

static size_t cmdLine_read(char* str, size_t max)
{
	if (HAL_UART_Receive(&huart1, (uint8_t*)str, max, 1) == HAL_OK)
		return max - huart1.RxXferCount;

	return 0;
}

static size_t cmdLine_write(const char* format, va_list params)
{
	char buffer[128];
	int  len = vsnprintf(buffer, sizeof(buffer), format, params);
	if (len > 0)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, 1);
		return len;
	}
	return 0;
}

static void cliTask_Handler(void* data)
{
	CLI* cli = (CLI*)data;
	CLI_Process(cli);
}

void CMD_Setup()
{
	CLI_Init(&cmdLine, PROMPT, cmdList, cmdLine_read, cmdLine_write);
	Scheduler_CreateRecurringTask(&scheduler, &cliTask, TASK_CLI, cliTask_Handler, &cmdLine, CLI_PERIOD);
}
