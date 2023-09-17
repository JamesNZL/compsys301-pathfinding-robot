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
#ifdef SENSOR_DISPLAY_ON_DEBUG
		Sensor_write_statuses_to_debug();
#endif

		/* Turn Detection */
		if (FLAG_IS_CLEARED(FLAGS, FLAG_WAITING_AFTER_TURN))
		{
			if (Sensor_is_on_right_turn_intersection())
			{
				FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
				Movement_turn_right(90);
				CyDelay(100);
				Movement_sync_motors(MOVEMENT_SPEED_RUN);
				Movement_skew_correct(DIRECTION_LEFT, MOVEMENT_SKEW_BOOST);
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
				Movement_skew_correct(DIRECTION_RIGHT, MOVEMENT_SKEW_BOOST);
				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_TURN);

				continue;
			}
		}

		/* Sensor Actions */
		static SensorActions previousAction = SENSOR_ACTION_CONTINUE_FORWARD;
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

#ifndef SENSOR_DISPLAY_ON_DEBUG
			DB0_OFF;
			DB1_OFF;
			DB2_OFF;
			DB3_OFF;
			DB4_OFF;
			DB5_OFF;
			DB6_OFF;
			DB7_OFF;
#endif

			break;
		}
		case SENSOR_ACTION_CONTINUE_PREVIOUS:
		{
			continue;
		}
		case SENSOR_ACTION_CORRECT_LEFT:
		{
			Movement_skew_correct(DIRECTION_LEFT, 0);

#ifndef SENSOR_DISPLAY_ON_DEBUG
			DB0_ON;
			DB1_ON;
			DB2_ON;
			DB3_ON;
			DB4_OFF;
			DB5_OFF;
			DB6_OFF;
			DB7_OFF;
#endif

			break;
		}
		case SENSOR_ACTION_CORRECT_RIGHT:
		{
			Movement_skew_correct(DIRECTION_RIGHT, 0);

#ifndef SENSOR_DISPLAY_ON_DEBUG
			DB0_OFF;
			DB1_OFF;
			DB2_OFF;
			DB3_OFF;
			DB4_ON;
			DB5_ON;
			DB6_ON;
			DB7_ON;
#endif

			break;
		}
		case SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT:
		{
			Motor_Control_Reg_Write(Motor_Control_Reg_Read() | (1 << MOTOR_DISABLE_CR_POS));

			// Movement_sync_mmotors(170);
			break;
		}
		case SENSOR_ACTION_FIND_VALID_STATE:
		{
			Motor_Control_Reg_Write(Motor_Control_Reg_Read() | (1 << MOTOR_DISABLE_CR_POS));

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