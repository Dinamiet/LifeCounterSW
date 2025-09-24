#ifndef _CMD_LIST_H_
#define _CMD_LIST_H_

#include "cli.h"

void                     display_Cmd(const CLI* cli, const size_t argc, char* const argv[]);
extern const char* const display_Help[];

void                     buzzer_Cmd(const CLI* cli, const size_t argc, char* const argv[]);
extern const char* const buzzer_Help[];

void                     poweroff_Cmd(const CLI* cli, const size_t argc, char* const argv[]);
extern const char* const poweroff_Help[];

#endif
