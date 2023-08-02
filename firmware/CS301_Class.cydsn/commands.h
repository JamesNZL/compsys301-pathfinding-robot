#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#define COMMAND_DELIMITER " "

/**
 * @brief The `switch`-able enumeration value that is mapped to by a command string.
 */
typedef enum CommandEnumeration
{
	COMMAND_CHANGE_DUTY,
	COMMAND_CHANGE_DIRECTION,
	COMMAND_CHANGE_SPEED,
	COMMAND_NOT_FOUND,
} CommandEnumeration;

/**
 * @brief A command that is parsable by the robot.
 */
typedef struct Command
{
	/**
	 * @brief The command keyword as a null-terminated C string.
	 */
	char *keyword;
	/**
	 * @brief The command enumeration.
	 */
	CommandEnumeration enumeration;
} Command;

/**
 * @brief The list of all recognised commands.
 */
static const Command COMMAND_LIST[4] = {
	{"CHG_DUTY", COMMAND_CHANGE_DUTY},
	{"CHG_DIR", COMMAND_CHANGE_DIRECTION},
	{"CHG_SPEED", COMMAND_CHANGE_SPEED},
	{NULL, COMMAND_NOT_FOUND},
};

/**
 * @brief Attempt to match a null-terminated C string to a recognised command enumeration.
 *
 * @param command The null-terminated C string to parse as a command keyword.
 * @return CommandEnumeration The matched command enumeration, or COMMAND_NOT_FOUND if unsuccessful.
 */
CommandEnumeration Commands_match_command(char *command);

#endif