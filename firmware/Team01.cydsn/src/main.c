#include "battery.h"
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
volatile SensorActions previousAction = SENSOR_ACTION_CONTINUE_FORWARD;
volatile SensorActions currentAction;

int main()
{
	CYGlobalIntEnable;

	uint16 batteryVoltage = Battery_display_level();
	sprintf(USB_buffer, "Battery Voltage: %d mV\n", batteryVoltage);

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);

	USB_put_string(USB_buffer);
#endif

	while (Push_Button_Read() != TRUE)
	{
		;
	}

	Sensor_init_sensors();
	Movement_init_motors();

	FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
	Movement_sync_motors(MOVEMENT_SPEED_RUN);

	for (;;)
	{
		/*
		 * Movement Control
		 */
		Movement_next_control_cycle();
		Movement_check_distance();
		Sensor_write_statuses_to_debug();

		/* Turn Detection */
		if (FLAG_IS_CLEARED(FLAGS, FLAG_WAITING_AFTER_TURN))
		{
			if (Sensor_is_on_right_turn_intersection())
			{
				FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
				Movement_turn_right(90);
				CyDelay(100);
				Movement_sync_motors(MOVEMENT_SPEED_RUN);
				Movement_skew_correct(DIRECTION_LEFT);
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_TURN);
				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

				continue;
			}
			else if (Sensor_is_on_left_turn_intersection())
			{
				FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
				Movement_turn_left(90);
				CyDelay(100);
				Movement_sync_motors(MOVEMENT_SPEED_RUN);
				Movement_skew_correct(DIRECTION_RIGHT);
				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_TURN);

				continue;
			}
		}

		/* Sensor Actions */
		SensorActions currentAction = Sensor_determine_action();
		if (currentAction == previousAction)
		{
			continue;
		}

		switch (currentAction)
		{
		case SENSOR_ACTION_CONTINUE_FORWARD:
		{
			Movement_sync_motors(MOVEMENT_SPEED_RUN);
			break;
		}
		case SENSOR_ACTION_CONTINUE_PREVIOUS:
		{
			continue;
		}
		case SENSOR_ACTION_CORRECT_LEFT:
		{
			Movement_skew_correct(DIRECTION_LEFT);
			break;
		}
		case SENSOR_ACTION_CORRECT_RIGHT:
		{
			Movement_skew_correct(DIRECTION_RIGHT);
			break;
		}
		case SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT:
		{
			// Movement_sync_mmotors(170);
			break;
		}
		}
		previousAction = currentAction;

#ifdef USB_ENABLED
		/*
		 * Command Parsing
		 */
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