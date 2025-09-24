// clang-format off
#include "usart.h"
// clang-format on
#include "cmd.h"
#include "cmdList.h"
#include "fifobuffer.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

#define PROMPT ">>"
#define CMD(x) {#x, x##_Cmd, x##_Help}

static CLI           cmdLine;
static SchedulerTask cliTask;
static uint8_t       uartITBuffer;
static uint8_t       cliReceiveBuffer[128];
static FifoBuffer    cliFifoBuffer;

static size_t cmdLine_read(char* str, size_t max);
static size_t cmdLine_write(const char* format, va_list params);
static void   cliTask_Handler(void* data);

static CLICommand cmdList[] = {
		CMD(display),
		CMD(buzzer),
		CMD(poweroff),
		{"help", CLI_Cmd, CLI_Help},
		{  NULL,    NULL,     NULL}
};

static size_t cmdLine_read(char* str, size_t max) { return FifoBuffer_Remove(&cliFifoBuffer, str, max); }

static size_t cmdLine_write(const char* format, va_list params)
{
	char buffer[128];
	int  len = vsnprintf(buffer, sizeof(buffer), format, params);
	if (len > 0)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, HAL_MAX_DELAY);
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
	FifoBuffer_Init(&cliFifoBuffer, cliReceiveBuffer, sizeof(cliReceiveBuffer));
	CLI_Init(&cmdLine, PROMPT, cmdList, cmdLine_read, cmdLine_write);
	Scheduler_CreateRecurringTask(&scheduler, &cliTask, TASK_CLI, cliTask_Handler, &cmdLine, CLI_PERIOD);

	HAL_UART_Receive_IT(&huart1, &uartITBuffer, sizeof(uartITBuffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	FifoBuffer_Add(&cliFifoBuffer, &uartITBuffer, sizeof(uartITBuffer));
	HAL_UART_Transmit(huart, &uartITBuffer, sizeof(uartITBuffer), 1); // Echo back the received character
	HAL_UART_Receive_IT(huart, &uartITBuffer, sizeof(uartITBuffer));
}
