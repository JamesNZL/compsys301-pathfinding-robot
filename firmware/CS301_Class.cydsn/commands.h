#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#define COMMAND_DELIMITER " "

typedef enum CommandEnumeration
{
	COMMAND_CHANGE_DUTY,
	COMMAND_CHANGE_DIRECTION,
	COMMAND_NOT_FOUND,
} CommandEnumeration;

typedef struct Command
{
	char *command;
	CommandEnumeration enumeration;
} Command;

static const Command COMMAND_LIST[3] = {
	{ "CHG_DUTY", COMMAND_CHANGE_DUTY },
	{ "CHG_DIR", COMMAND_CHANGE_DIRECTION },
	{ NULL, COMMAND_NOT_FOUND },
};

CommandEnumeration match_command(char *command);

#endif