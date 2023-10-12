#include "battery.h"
#include "buzza.h"
#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "map2.h"
#include "movement.h"
#include "pathfinding.h"
#include "sensor.h"
#include "usb.h"

#include <Point/Point.h>

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define FIXED_DISTANCE
#define PATHFINDING
// #define TROLLING

volatile uint16 FLAGS = 0x00;

int main()
{
	CYGlobalIntEnable;

#ifdef TROLLING
	PWM_Play_Buzzer_Start();
	BUZZA_USE_PWM_MODE;
	Buzza_play_pwm(BUZZA_SONG(BUZZA_SONG_TO_PLAY), 0);
#endif
	uint16 batteryVoltage = Battery_display_level();
	sprintf(USB_buffer, "Battery Voltage: %d mV\n", batteryVoltage);

/* Pathfinding init */
#ifdef PATHFINDING
	// Always constant
	Point *startPoint = Point_create(PATHFINDING_START_X, PATHFINDING_START_Y, PATHFINDING_MAZE_WIDTH);
	Queue *routes = Pathfinding_generate_routes_to_all_food(
		startPoint,
		PATHFINDING_STARTING_DIRECTION,
		PATHFINDING_FOOD_LIST,
		PATHFINDING_MAZE);
	Point_destroy(startPoint);

	// Will change during runtime **MUST FREE**
	Node *currentNode = Queue_pop(routes);
	PathfindingRoute *currentRoute = Node_get_value(currentNode);
	Queue *currentRouteActions = Pathfinding_route_get_actions(currentRoute);
	Actions *currentActionToCheckFor;

	if (!Queue_is_empty(currentRouteActions))
	{
		// Node_destroy(currentNode);
		currentNode = Queue_pop(currentRouteActions);
		currentActionToCheckFor = Node_get_value(currentNode);
		if (Queue_is_empty(currentRouteActions))
		{
			FLAG_SET(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE);
		}
	}
	else
	{
		FLAG_SET(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED);
	}

#endif

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);

	USB_put_string(USB_buffer);
#endif

	Sensor_init_sensors();
	while (Push_Button_Read() != TRUE)
	{
		;
	}

	DEBUG_ALL_OFF;

	Movement_init_motors();

#ifdef FIXED_DISTANCE
	Movement_move_mm(1000);
#else
	FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
#endif
	Movement_sync_motors(MOVEMENT_SPEED_RUN);

	static SensorActions previousAction;
	static SensorActions currentAction;

	for (;;)
	{
		CyDelay(10);
#ifdef SENSOR_DEBUG
		Sensor_write_statuses_to_debug();
#endif

		/*
		 * Movement Control
		 */

		/* Turn Detection */
		if (FLAG_IS_SET(FLAGS, FLAG_WAITING_AFTER_ACTION))
		{
#ifdef MOVEMENT_DEBUG_TURNS
			DEBUG_ALL_ON;
#endif
			Movement_check_action_complete();
		}
		else
		{
#ifdef PATHFINDING
			// if we are not moving mm
			if (FLAG_IS_CLEARED(FLAGS, FLAG_MOVING_MM))
			{
				// restart motors in case where we enter the next route in between intersections
				if (FLAG_IS_CLEARED(FLAGS, FLAG_MOVE_INFINITELY) && FLAG_IS_CLEARED(FLAGS, FLAG_DOING_LAST_MOVE_MM))
				{
					FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);
					Movement_sync_motors(MOVEMENT_SPEED_RUN);
					continue;
				}
				// check if we have actions left to do for the current route
				if (!Queue_is_empty(currentRouteActions) || FLAG_IS_SET(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE))
				{
					if (FLAG_IS_SET(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED))
					{
						FLAG_CLEAR(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED);
					}
					switch (*currentActionToCheckFor)
					{
					case ACTIONS_AROUND:
					{
#ifdef DEBUG_PATHFINDING
						DEBUG_ALL_OFF;
#endif

						FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);
#ifdef TROLLING
						Buzza_play_song(BUZZA_SONG(BUZZA_SONG_TO_PLAY));
#endif
						FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
						FLAG_SET(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);

						Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
						Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
						Movement_sync_motors(MOVEMENT_SPEED_OFF);

						Movement_turn_left(180, Sensor_is_any_front_on_line);
						CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

						Movement_sync_motors(MOVEMENT_SPEED_SLOW);
						Movement_skew_correct(DIRECTION_LEFT);
						previousAction = SENSOR_ACTION_CORRECT_LEFT;

						FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

						Node_destroy(currentNode);
						currentNode = Queue_pop(currentRouteActions);
						currentActionToCheckFor = Node_get_value(currentNode);

						Pathfinding_check_if_waiting_for_final_action_in_queue(currentRouteActions);
						continue;
					}
					case ACTIONS_LEFT:
					{
#ifdef DEBUG_PATHFINDING
						DEBUG_ALL_OFF;
						DEBUG_LEFT_ON;
#endif
						if (Sensor_has_left_turn())
						{
#ifdef MOVEMENT_DEBUG_SKEW
							DEBUG_ALL_OFF;
							DEBUG_LEFT_ON;
#endif
							FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
							FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);
							FLAG_SET(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);

							Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
							Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
							Movement_sync_motors(MOVEMENT_SPEED_OFF);

							Movement_turn_left(90, Sensor_is_any_front_on_line);
							CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

							Movement_sync_motors(MOVEMENT_SPEED_SLOW);
							Movement_skew_correct(DIRECTION_LEFT);
							previousAction = SENSOR_ACTION_CORRECT_LEFT;

							FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

							Node_destroy(currentNode);
							currentNode = Queue_pop(currentRouteActions);
							currentActionToCheckFor = Node_get_value(currentNode);

							Pathfinding_check_if_waiting_for_final_action_in_queue(currentRouteActions);
							continue;
						}
						break;
					}
					case ACTIONS_RIGHT:
					{
#ifdef DEBUG_PATHFINDING
						DEBUG_ALL_OFF;
						DEBUG_RIGHT_ON;
#endif
						if (Sensor_has_right_turn())
						{

#ifdef MOVEMENT_DEBUG_SKEW
							DEBUG_ALL_OFF;
							DEBUG_RIGHT_ON;
#endif
							FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
							FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);
							FLAG_SET(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);

							Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
							Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
							Movement_sync_motors(MOVEMENT_SPEED_OFF);

							Movement_turn_right(90, Sensor_is_any_front_on_line);
							CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

							Movement_sync_motors(MOVEMENT_SPEED_SLOW);
							Movement_skew_correct(DIRECTION_RIGHT);
							previousAction = SENSOR_ACTION_CORRECT_RIGHT;

							FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

							Node_destroy(currentNode);
							currentNode = Queue_pop(currentRouteActions);
							currentActionToCheckFor = Node_get_value(currentNode);

							Pathfinding_check_if_waiting_for_final_action_in_queue(currentRouteActions);
							continue;
						}
						break;
					}
					case ACTIONS_SKIP:
					{
#ifdef DEBUG_PATHFINDING
						DEBUG_ALL_OFF;
						DEBUG_ALL_ON;
#endif
						if (Sensor_has_turn())
						{
							FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);

							Node_destroy(currentNode);
							currentNode = Queue_pop(currentRouteActions);
							currentActionToCheckFor = Node_get_value(currentNode);

							Pathfinding_check_if_waiting_for_final_action_in_queue(currentRouteActions);
							continue;
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				// if the current route is empty -> we need to travel the final distance and prepare the next route
				else if (FLAG_IS_CLEARED(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE))
				{

#ifdef DEBUG_PATHFINDING
					// Queue IS empty
					DEBUG_ALL_ON;
#endif

					FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
					FLAG_SET(FLAGS, FLAG_MOVING_MM);

					MazeDirections lastFacedDirection = Pathfinding_route_get_last_faced_direction(currentRoute);
					uint8 finalGrids = Pathfinding_route_get_final_distance(currentRoute) - 1;

					if (Pathfinding_is_moving_horizontally(lastFacedDirection))
					{
						if (FLAG_IS_SET(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED))
						{
							Movement_move_mm(GRID_DISTANCE_LUT_MM_X[finalGrids]);
						}
						else
						{
							Movement_move_mm(GRID_DISTANCE_LUT_MM_X[finalGrids] - PATHFINDING_OVERSHOOT_REDUCTION_X);
						}
					}
					else if (Pathfinding_is_moving_vertically(lastFacedDirection))
					{
						if (FLAG_IS_SET(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED))
						{
							Movement_move_mm(GRID_DISTANCE_LUT_MM_Y[finalGrids]);
						}
						else
						{
							Movement_move_mm(GRID_DISTANCE_LUT_MM_Y[finalGrids] - PATHFINDING_OVERSHOOT_REDUCTION_Y);
						}
					}

					if (Queue_is_empty(routes))
					{
						FLAG_SET(FLAGS, FLAG_DOING_LAST_MOVE_MM);
						continue;
					}
					currentNode = Queue_pop(routes);
					currentRoute = Node_get_value(currentNode);
					// Node_destroy(currentNode);

					currentRouteActions = Pathfinding_route_get_actions(currentRoute);

					if (Queue_is_empty(currentRouteActions))
					{
						FLAG_SET(FLAGS, FLAG_NO_OVERSHOOT_CORRECTION_NEEDED);
						continue;
					}

					currentNode = Queue_pop(currentRouteActions);
					currentActionToCheckFor = Node_get_value(currentNode);
					Pathfinding_check_if_waiting_for_final_action_in_queue(currentRouteActions);
				}
			}
#else
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
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);
				FLAG_SET(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);

				Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
				Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
				Movement_sync_motors(MOVEMENT_SPEED_OFF);

				Movement_turn_right(90, Sensor_is_any_front_on_line);
				CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_RIGHT);
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
				FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);
				FLAG_SET(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);

				Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
				Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
				Movement_sync_motors(MOVEMENT_SPEED_OFF);

				Movement_turn_left(90, Sensor_is_any_front_on_line);
				CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_LEFT);
				previousAction = SENSOR_ACTION_CORRECT_LEFT;

				FLAG_SET(FLAGS, FLAG_MOVE_INFINITELY);

				continue;
			}
#endif
		}

		/* Movement Control Loop */
		Movement_next_control_cycle();
		Movement_check_distance();

		/* Sensor Actions */
		currentAction = Sensor_determine_action();
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
			DEBUG_OUTER_ON;
			DEBUG_RIGHT_OFF;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
				// Slow down the robot if we are snaking
				//	Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			}

			Movement_skew_correct(DIRECTION_LEFT);

			break;
		}
		case SENSOR_ACTION_CORRECT_RIGHT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_OUTER_ON;
			DEBUG_LEFT_OFF;
#endif
			if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
			{
				// Slow down the robot if we are snaking
				// Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			}

			Movement_skew_correct(DIRECTION_RIGHT);

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
			DEBUG_OUTER_ON;
			DEBUG_RIGHT_OFF;
#endif
			Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			Movement_skew_correct(DIRECTION_LEFT);

			break;
		}

		case SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT:
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_EVEN_ON;
#endif

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

				Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
				Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);

				break;
			}
			case SENSOR_ACTION_CONTINUE_FORWARD:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
#endif

				Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
				Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);

				break;
			}
			case SENSOR_ACTION_CORRECT_LEFT:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
				DEBUG_RIGHT_OFF;
#endif
				Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
				Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_LEFT);

				break;
			}
			case SENSOR_ACTION_CORRECT_RIGHT:
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
				DEBUG_LEFT_OFF;
#endif
				Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
				Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);
				Movement_skew_correct(DIRECTION_RIGHT);

				break;
			}
			default:
			{
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
#ifdef SENSOR_ACTIONS_INVALID_KILL
				MOVEMENT_DISABLE;
#endif
				Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
				Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
				Movement_sync_motors(MOVEMENT_SPEED_SLOW);

				if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
				{
#ifdef MOVEMENT_DEBUG_SKEW
					DEBUG_RIGHT_OFF;
#endif
					Movement_skew_correct(DIRECTION_LEFT);
				}
				else if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
				{
#ifdef MOVEMENT_DEBUG_SKEW
					DEBUG_LEFT_OFF;
#endif
					Movement_skew_correct(DIRECTION_RIGHT);
				}

				break;
			}
			}

			FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);

			CyDelay(MOVEMENT_RECOVERY_DELAY_PERIOD);
#else
			if (previousAction == SENSOR_ACTION_CORRECT_LEFT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
				DEBUG_RIGHT_OFF;
#endif
				Movement_skew_correct(DIRECTION_LEFT);

				break;
			}
			else if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
				DEBUG_LEFT_OFF;
#endif
				Movement_skew_correct(DIRECTION_RIGHT);

				break;
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
				DEBUG_OUTER_ON;
				DEBUG_RIGHT_OFF;
#endif
				Movement_skew_correct(DIRECTION_LEFT);

				break;
			}
			else if (previousAction == SENSOR_ACTION_CORRECT_RIGHT)
			{
#ifdef MOVEMENT_DEBUG_SKEW
				DEBUG_ALL_OFF;
				DEBUG_OUTER_ON;
				DEBUG_LEFT_OFF;
#endif
				Movement_skew_correct(DIRECTION_RIGHT);

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

			SensorActions action = Movement_sweep(Sensor_is_any_front_on_line, SENSOR_ACTION_TURN_ABOUT);
			if (action == SENSOR_ACTION_TURN_ABOUT)
			{
				// No line was detected in front—now sweep the back sensors
				action = Movement_sweep(Sensor_is_any_back_on_line, SENSOR_ACTION_CONTINUE_FORWARD);
			}

			FLAG_SET(FLAGS, FLAG_WAITING_AFTER_ACTION);

			// TODO: do I want the robot to move here? probably not
			// Movement_write_M1_pulse(MOVEMENT_SPEED_SLOW);
			// Movement_write_M2_pulse(MOVEMENT_SPEED_SLOW);
			Movement_sync_motors(MOVEMENT_SPEED_SLOW);
			// CyDelay(MOVEMENT_RECOVERY_DELAY_PERIOD);
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