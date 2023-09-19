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

// #define FIXED_DISTANCE

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

	DEBUG_ALL_OFF;

	Sensor_init_sensors();
	Movement_init_motors();

#ifdef FIXED_DISTANCE
	Movement_move_mm(1680);
#else
	FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
#endif
	Movement_sync_motors(MOVEMENT_SPEED_RUN);

	static SensorActions previousAction;
	static SensorActions currentAction;

	for (;;)
	{
#ifdef SENSOR_DEBUG
		Sensor_write_statuses_to_debug();
#endif

		/*
		 * Movement Control
		 */

		/* Turn Detection */
		// TODO: disable if just recovered from invalid state
		if (FLAG_IS_SET(FLAGS, FLAG_WAITING_AFTER_TURN))
		{
#ifdef MOVEMENT_DEBUG_TURNS
			DEBUG_ALL_ON;
#endif
			Movement_check_turn_complete();
		}
		else
		{
#ifdef MOVEMENT_DEBUG_TURNS
			DEBUG_ALL_OFF;
#endif
			if (Sensor_is_on_right_turn_intersection())
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_RIGHT_ON;
#endif
				FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_TURN);

				Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
				Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
				Movement_sync_motors(MOVEMENT_SPEED_OFF);

				Movement_turn_right(90, Sensor_is_any_front_on_line);
				CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_RIGHT, MOVEMENT_SKEW_BOOST_FACTOR);
				previousAction = SENSOR_ACTION_CORRECT_RIGHT;

				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

				continue;
			}
			else if (Sensor_is_on_left_turn_intersection())
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LEFT_ON;
#endif
				FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_TURN);

				Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
				Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
				Movement_sync_motors(MOVEMENT_SPEED_OFF);

				Movement_turn_left(90, Sensor_is_any_front_on_line);
				CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_LEFT, MOVEMENT_SKEW_BOOST_FACTOR);
				previousAction = SENSOR_ACTION_CORRECT_LEFT;

				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

				continue;
			}
		}

		/* Movement Control Loop */
		Movement_next_control_cycle();
		Movement_check_distance();

		/* Sensor Actions */
		currentAction = Sensor_determine_action();
		// TODO: disable sensing for x pulses
		if (currentAction == previousAction)
		{
			continue;
		}

		switch (currentAction)
		{

		case SENSOR_ACTION_CONTINUE_FORWARD:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
#endif
			Movement_sync_motors(MOVEMENT_SPEED_RUN);

			break;
		}

		case SENSOR_ACTION_ANTICIPATE_TURN:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_ON;
#endif
			Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
			Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
			Movement_sync_motors(MOVEMENT_SPEED_SLOW);

			break;
		}

		case SENSOR_ACTION_CONTINUE_PREVIOUS:
		{
			break;
		}

		case SENSOR_ACTION_CORRECT_LEFT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_LEFT_ON;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
				// Slow down the robot if we are snaking
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			}

			Movement_skew_correct(DIRECTION_LEFT, MOVEMENT_SKEW_BOOST_FACTOR);

			break;
		}

		case SENSOR_ACTION_CORRECT_RIGHT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_RIGHT_ON;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
			{
				// Slow down the robot if we are snaking
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			}

			Movement_skew_correct(DIRECTION_RIGHT, MOVEMENT_SKEW_BOOST_FACTOR);

			break;
		}

		case SENSOR_ACTION_TURN_ABOUT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_LOWER_ON;
#endif
			Movement_turn_right(180, Sensor_is_any_front_on_line);

#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_LEFT_ON;
#endif
			Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			Movement_skew_correct(DIRECTION_LEFT, MOVEMENT_SKEW_BOOST_FACTOR);

			break;
		}

		case SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_EVEN_ON;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LEFT_ON;
#endif
				Movement_skew_correct(DIRECTION_LEFT, 0);

				break;
			}
			else if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_RIGHT_ON;
#endif
				Movement_skew_correct(DIRECTION_RIGHT, 0);

				break;
			}

#ifdef SENSOR_ACTIONS_RIGOROUS
			/*
				Rotate left and right to see if just skewed
				(ie if front sensor(s) return to line),
				otherwise turn around
			 */

			Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
			Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
			Movement_sync_motors(MOVEMENT_SPEED_OFF);

			SensorActions action = Movement_sweep(Sensor_is_any_front_on_line, SENSOR_ACTION_TURN_ABOUT);
			switch (action)
			{
			case SENSOR_ACTION_TURN_ABOUT:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LOWER_ON;
#endif
				Movement_turn_right(180, Sensor_is_any_front_on_line);

#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LEFT_ON;
#endif
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);

				break;
			}
			// TODO: keep driving until middle sensor returns
			case SENSOR_ACTION_CORRECT_LEFT:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LEFT_ON;
#endif
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_LEFT, MOVEMENT_SKEW_BOOST_FACTOR);

				break;
			}
			case SENSOR_ACTION_CORRECT_RIGHT:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_RIGHT_ON;
#endif
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_RIGHT, MOVEMENT_SKEW_BOOST_FACTOR);

				break;
			}
			default:
			{
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
#ifdef SENSOR_ACTIONS_INVALID_KILL
				MOVEMENT_DISABLE;
#endif
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);

				break;
			}
			}
#endif
			break;
		}

		case SENSOR_ACTION_FIND_VALID_STATE:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_ODD_ON;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_LEFT_ON;
#endif
				Movement_skew_correct(DIRECTION_LEFT, 0);

				break;
			}
			else if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_RIGHT_ON;
#endif
				Movement_skew_correct(DIRECTION_RIGHT, 0);

				break;
			}

#ifdef SENSOR_ACTIONS_RIGOROUS
			/*
				Rotate left and right to transition to a valid state
				—ignore rear skew detection unless front detectors do not detect anything
				—this is to prevent the robot from turning around when it should continue forward
			 */

			Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
			Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
			Movement_sync_motors(MOVEMENT_SPEED_OFF);

			// TODO: why do i need this switch case? does it not properly return to the line?
			SensorActions action = Movement_sweep(Sensor_is_any_front_on_line, SENSOR_ACTION_TURN_ABOUT);
			if (action == SENSOR_ACTION_TURN_ABOUT)
			{
				// No line was detected in front—now sweep the back sensors
				action = Movement_sweep(Sensor_is_any_back_on_line, SENSOR_ACTION_CONTINUE_FORWARD);
			}

			Movement_sync_motors(MOVEMENT_SPEED_SLOW);
#endif
			break;
		}

		default:
		{
			DEBUG_ALL_OFF;
			DEBUG_OUTER_ON;
			MOVEMENT_DISABLE;

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