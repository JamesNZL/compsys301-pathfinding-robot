#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "movement.h"
#include "sensor.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8 FLAGS = 0x00;

int main()
{
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();
	QuadDec_M1_Start();
	QuadDec_M2_Start();
	Sensor_init_sensors();
#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif
	while (Push_Button_Read() != TRUE)
	{
		;
	}

	for (;;)
	{
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
		if (Sensor_is_on_right_turn_intersection())
		{
			Movement_turn_right(90);
			CyDelay(3000);
		}
		else if (Sensor_is_on_left_turn_intersection())
		{
			Movement_turn_left(90);
			CyDelay(3000);
		}
		Sensor_write_statuses_to_debug();
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