#include "commands.h"

#include <cytypes.h>
#include <string.h>

CommandEnumeration Commands_match_command(char *command)
{
	for (uint8 i = 0; COMMAND_LIST[i].enumeration != COMMAND_NOT_FOUND; i++)
	{
		uint8 commandLength = strlen(COMMAND_LIST[i].keyword);

		// Check that the incoming command is the correct length
		if (command[commandLength] != '\0')
		{
			return COMMAND_NOT_FOUND;
		}

		if (strncmp(command, COMMAND_LIST[i].keyword, commandLength) == 0)
		{
			return COMMAND_LIST[i].enumeration;
		}
	}

	return COMMAND_NOT_FOUND;
}