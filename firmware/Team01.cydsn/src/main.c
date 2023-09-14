#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "movement.h"
#include "pathfinding.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8 FLAGS = 0x00;

char *action_strings[5] = {
	"left", "right", "skip", "around", "straight"
};

char *direction_strings[4] = {
	"left", "right", "up", "down"
};

uint8_t map[15][19] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

uint8_t food_list[5][2] = {
	{ 1, 9 },
	{ 5, 5 },
	{ 7, 1 },
	{ 13, 5 },
	{ 9, 9 },
};
int main()
{
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	Point *start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Queue *routes = Pathfinding_generate_routes_to_all_food(start, MAZE_DIRECTIONS_DOWN, food_list, map);
	char buffer[256];
	RF_BT_SELECT_Write(0);
	while (!Queue_is_empty(routes))
	{
		Node *current_node = Queue_pop(routes);
		PathfindingRoute *current_route = Node_get_value(current_node);
		Queue *turns = Pathfinding_route_get_turns(current_route);
		while (!Queue_is_empty(turns))
		{
			Node *current = Queue_pop(turns);
			Actions *current_action = Node_get_value(current);
			sprintf(buffer, "%s,", action_strings[*current_action]);
			USB_put_string(buffer);
			free(current_action);
			Node_destroy(current);
		}

		sprintf(buffer, "\nThe last facing direction is: %s\n", direction_strings[Pathfinding_route_get_last_faced_direction(current_route)]);
		USB_put_string(buffer);
		sprintf(buffer, "The final required distance is: %i\n", Pathfinding_route_get_final_distance(current_route));
		USB_put_string(buffer);
		Node_destroy(current_node);
		Pathfinding_route_destroy(current_route);
	}
	for (;;)
	{
		/* Place your application code here. */
		USB_get_input();

		if (FLAG_IS_SET(FLAGS, FLAG_USB_INPUT))
		{
			FLAGS_CLEAR(FLAGS, FLAG_USB_INPUT);

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
	}
}