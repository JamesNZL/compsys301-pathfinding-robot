#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#define COMMAND_DELIMITER " "

typedef enum CommandSymbol
{
	COMMAND_CHANGE_DUTY,
	COMMAND_CHANGE_DIRECTION,
	COMMAND_NOT_FOUND,
} CommandSymbol;

typedef struct Command
{
	char *command;
	CommandSymbol symbol;
} Command;

static const Command COMMAND_LIST[3] = {
	{ "CHG_DUTY", COMMAND_CHANGE_DUTY },
	{ "CHG_DIR", COMMAND_CHANGE_DIRECTION },
	{ NULL, COMMAND_NOT_FOUND },
};

CommandSymbol matchCommand(char *command);

#endif