#include "commands.h"
#include "handlers.h"
#include "movement.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();

#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	RF_BT_SELECT_Write(0);

	for (;;)
	{
		/* Place your application code here. */
		handle_usb();
		if (flag_KB_string == 1)
		{
			char *token = strtok(line, COMMAND_DELIMITER);
			if (token != NULL)
			{
				switch (Commands_match_command(token))
				{
				case (COMMAND_CHANGE_DIRECTION):
				{
					usb_put_string("Parsed command: CHANGE_DIRECTION\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_direction(token);
					break;
				}
				case (COMMAND_CHANGE_DUTY):
				{
					usb_put_string("Parsed command: CHANGE_DUTY\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					break;
				}
				case (COMMAND_CHANGE_SPEED):
				{
					usb_put_string("Parsed command: CHANGE_DUTY\n");
					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_speed(token);
					break;
				}
				default:
				{
					usb_put_string("Failed to parse command.\n");
					usb_put_string("You Sent:\n");
					usb_put_string(token);
					usb_put_string("\n");
					break;
				}
				}
			}
			flag_KB_string = 0;
		}
	}
}