#include "handlers.h"
#include "commands.h"
#include "common.h"
#include "movement.h"
#include "usb.h"

#include <stdlib.h>
#include <string.h>

void Handlers_change_direction(char *token)
{

	if (token != NULL)
	{
		if (strcmp(token, "F") == 0)
		{
			Movement_set_direction(DIRECTION_FORWARD);
		}
		else if (strcmp(token, "R") == 0)
		{
			Movement_set_direction(DIRECTION_REVERSE);
		}
	}
}

void Handlers_change_speed(char *token)
{
	MOVEMENT_RUN_SPEED = atoi(token);
}