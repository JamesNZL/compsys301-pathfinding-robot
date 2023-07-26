#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#define COMMAND_DELIMITER " "

typedef enum CommandSymbol
{
	COMMAND_CHANGE_DUTY,
	COMMAND_NOT_FOUND,
} CommandSymbol;

typedef struct Command
{
	char *command;
	CommandSymbol symbol;
} Command;

static const Command COMMAND_LIST[2] = {
	{ "ChgD", COMMAND_CHANGE_DUTY },
	{ NULL, COMMAND_NOT_FOUND },
};

CommandSymbol matchCommand(char *command);

#endif