#include "battery.h"
#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "movement.h"
#include "sensor.h"
#include "sfx.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8 FLAGS = 0x00;

int main()
{
	CYGlobalIntEnable;
	uint16 batteryVoltage = Battery_display_level();
	sprintf(USB_buffer, "Battery Voltage: %d mV\n", batteryVoltage);
	Sfx_scream();

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);

	USB_put_string(USB_buffer);
#endif

	while (Push_Button_Read() != TRUE)
	{
		;
	}

	Movement_init_motors();
	Sensor_init_sensors();

	Movement_move_mm(2000);
	Movement_sync_motors(300);

	for (;;)
	{
		Movement_next_control_cycle();
		Movement_check_distance();

		Sensor_write_statuses_to_debug();
		SensorActions currentAction = Sensor_determine_action();
		switch (currentAction)
		{
		case SENSOR_ACTION_CONTINUE_FORWARD:
		{
			break;
		}
		case SENSOR_ACTION_CONTINUE_PREVIOUS:
		{
			break;
		}
		case SENSOR_ACTION_CORRECT_LEFT:
		{
			break;
		}
		case SENSOR_ACTION_CORRECT_RIGHT:
		{
			break;
		}
		case SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT:
		{
			break;
		}
		case SENSOR_ACTION_FIND_VALID_STATE:
		{
			break;
		}
		}
#ifdef USB_ENABLED
		/* Place your application code here. */
		USB_get_input();

		if (FLAG_IS_SET(FLAGS, FLAG_USB_INPUT))
		{
			FLAG_CLEAR(FLAGS, FLAG_USB_INPUT);

			char *token = strtok(USB_input, COMMAND_DELIMITER);
			if (token != NULL)
			{
				switch (Commands_match_command(token))
				{
				case (COMMAND_CHANGE_DIRECTION):
				{
					USB_put_string("Parsed command: CHANGE_DIRECTION\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_direction(token);
					break;
				}
				case (COMMAND_CHANGE_DUTY):
				{
					USB_put_string("Parsed command: CHANGE_DUTY\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					break;
				}
				case (COMMAND_CHANGE_SPEED):
				{
					USB_put_string("Parsed command: CHANGE_DUTY\n");
					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_speed(token);
					break;
				}
				default:
				{
					USB_put_string("Failed to parse command.\n");
					USB_put_string("You Sent:\n");
					USB_put_string(token);
					USB_put_string("\n");
					break;
				}
				}
			}
		}
#endif
	}
}