#include "commands.h"

#include <stdint.h>
#include <string.h>

CommandSymbol matchCommand(char *command)
{
	for (uint8_t i = 0; COMMAND_LIST[i].symbol != COMMAND_NOT_FOUND; i++)
	{
		uint8_t commandLength = strlen(COMMAND_LIST[i].command);

		// Check that the incoming command is the correct length
		if (command[commandLength] != '\0')
		{
			return COMMAND_NOT_FOUND;
		}

		if (strncmp(command, COMMAND_LIST[i].command, commandLength) == 0)
		{
			return COMMAND_LIST[i].symbol;
		}
	}

	return COMMAND_NOT_FOUND;
}