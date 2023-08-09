#include "handlers.h"
#include "commands.h"
#include "movement.h"
#include "usb.h"

#include <stddef.h>
#include <stdio.h>
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
	uint8_t percent = atoi(token);
	USB_put_string(token);
	Movement_set_speed(percent);
}