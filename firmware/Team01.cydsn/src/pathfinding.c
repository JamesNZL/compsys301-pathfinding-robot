#include "pathfinding.h"

const static int8_t dY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t dX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

/* Everything relating to the route data structure*/
typedef struct Pathfinding_route
{
	Queue *turns;
	Maze_Directions last_faced_direction;
	uint8_t final_distance;
} Pathfinding_route;

Pathfinding_route *Pathfinding_route_construct(Queue *turns, Maze_Directions last_faced_direction, uint8_t final_distance)
{
	Pathfinding_route *route = malloc(sizeof(Pathfinding_route));
	if (route == NULL)
	{
		return NULL;
	}
	route->turns = turns;
	route->last_faced_direction = last_faced_direction;
	route->final_distance = final_distance;
	return route;
}

Queue *Pathfinding_route_get_turns(Pathfinding_route *route)
{
	return route->turns;
}

Maze_Directions Pathfinding_route_get_last_faced_direction(Pathfinding_route *route)
{
	return route->last_faced_direction;
}

uint8_t Pathfinding_route_get_final_distance(Pathfinding_route *route)
{
	return route->final_distance;
}

/* END route operations */

Maze_Directions Pathfinding_get_relative_direction(Point *current, Point *next)
{
	uint8_t current_x = Point_get_x(current);
	uint8_t current_y = Point_get_y(current);
	uint8_t next_x = Point_get_x(next);
	uint8_t next_y = Point_get_y(next);

	// TODO: possible handle non-adjacent cases i.e throw error
	// is in a different X position
	if (current_x != next_x)
	{
		// next is on the left
		if (next_x < current_x)
		{
			return MAZE_DIRECTIONS_LEFT;
		}
		else
		{
			return MAZE_DIRECTIONS_RIGHT;
		}
	}
	else
	{
		// y is different
		if (next_y < current_y)
		{
			// next is above
			return MAZE_DIRECTIONS_UP;
		}
		else
		{
			return MAZE_DIRECTIONS_DOWN;
		}
	}
}
Actions Pathfinding_get_required_action(Maze_Directions current, Maze_Directions next)
{
	switch (current)
	{
	case MAZE_DIRECTIONS_LEFT:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_LEFT;
		}
	}
	break;
	case MAZE_DIRECTIONS_RIGHT:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_RIGHT;
		}
	}
	break;
	case MAZE_DIRECTIONS_UP:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_AROUND;
		}
	}
	break;
	case MAZE_DIRECTIONS_DOWN:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_STRAIGHT;
		}
	}
	break;
	}
	return ACTIONS_SKIP;
}

Stack *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	// predecessor array to store shortest path
	uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH];
	for (int i = 0; i < PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH; ++i)
	{
		pred[i] = UINT16_MAX; // initialize to "no predecessor"
	}

	uint8_t visited[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH] = { 0 };
	visited[Point_get_y(start)][Point_get_x(start)] = 1;
	Queue *q = Queue_construct();
	Queue_append(q, Node_create(start));
	Point *current_point;
	while (!Queue_is_empty(q))
	{
		Node *current_node = Queue_pop(q);
		current_point = Node_get_value(current_node);
		// printf("(%i,%i)", Point_get_x(current_point), Point_get_y(current_point));
		if (Point_equal(current_point, end))
		{
			Node_destroy(current_node);
			Point_destroy(current_point);
			break;
		}
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX = Point_get_x(current_point) + dX[i];
			uint8_t newY = Point_get_y(current_point) + dY[i];
			if (Pathfinding_coordinates_in_bounds(newX, newY) && !visited[newY][newX] && maze[newY][newX] == 0)
			{
				Point *neighbour_point = Point_create(newX, newY, PATHFINDING_MAZE_WIDTH);
				Node *neighbour = Node_create(neighbour_point);
				pred[Point_get_1d(neighbour_point)] = Point_get_1d(current_point);
				visited[newY][newX] = 1;
				Queue_append(q, neighbour);
			}
		}
		Node_destroy(current_node);
		Point_destroy(current_point);
	}
	Stack *stack = Stack_construct();
	Pathfinding_build_stack_from_pred(stack, pred, start, end);
	Queue_destroy(q);
	return stack;
}

Pathfinding_route *Pathfinding_generate_route_to_food(Stack *shortest_path, Maze_Directions starting_direction, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	Maze_Directions current_direction = starting_direction;
	Queue *turns = Queue_construct();
	Point *latest_intersection_point;

	while (!Stack_is_empty(shortest_path))
	{
		Node *current_node = Stack_pop(shortest_path);
		Point *current_point = Node_get_value(current_node);
		Node_destroy(current_node);
		// we popped the last node
		if (Stack_is_empty(shortest_path))
		{
			Stack_destroy(shortest_path);
			Point_destroy(current_point);
			break;
		}

		// dont destroy node here becauase we pop it next iteration
		Node *next_node = Stack_peek(shortest_path);
		Point *next_point = Node_get_value(next_node);

		Maze_Directions relative_direction_of_next = Pathfinding_get_relative_direction(current_point, next_point);
		Actions required_action = Pathfinding_get_required_action(current_direction, relative_direction_of_next);
		// Need a pointer to use node
		Actions *required_action_pointer = malloc(sizeof(Actions));

		current_direction = relative_direction_of_next;

		uint8_t current_x = Point_get_x(current_point);
		uint8_t current_y = Point_get_y(current_point);

		if (required_action == ACTIONS_STRAIGHT)
		{
			if (Pathfinding_is_on_intersection(current_direction, current_x, current_y, maze))
			{
				*required_action_pointer = ACTIONS_SKIP;
				Queue_append(turns, Node_create(required_action_pointer));
			}
			// no longer need point if its not part of an intersection
			Point_destroy(current_point);
		}
		else
		{
			latest_intersection_point = current_point;
			*required_action_pointer = required_action;
			Queue_append(turns, Node_create(required_action_pointer));
		}
	}
	Pathfinding_route *route = Pathfinding_route_construct(turns, current_direction, 0);
	return route;
}

void Pathfinding_build_stack_from_pred(Stack *stack, uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH], Point *start, Point *end)
{
	// start with final point
	uint16_t current_index = Point_get_1d(end);
	// use starting point to know if we've reached the end
	uint16_t start_index = Point_get_1d(start);
	while (current_index != UINT16_MAX && current_index != start_index)
	{
		// printf("%i\n", current_index);
		Node *current_node = Node_create(Point_create_from_1d(current_index, PATHFINDING_MAZE_WIDTH));
		Stack_push(stack, current_node);
		current_index = pred[current_index];
	}
	// push the start node
	if (current_index == start_index)
	{
		Node *start_node = Node_create(Point_create_from_1d(start_index, PATHFINDING_MAZE_WIDTH));
		Stack_push(stack, start_node);
	}
}

uint8_t Pathfinding_is_on_intersection(Maze_Directions current_direction, uint8_t x, uint8_t y, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	switch (current_direction)
	{
	// moving horizontally
	case MAZE_DIRECTIONS_LEFT:
	case MAZE_DIRECTIONS_RIGHT:

		if (maze[y + 1][x] == 0 || maze[y - 1][x] == 0)
		{
			return 1;
		}
		break;
	// moving vertically
	case MAZE_DIRECTIONS_UP:
	case MAZE_DIRECTIONS_DOWN:
		if (maze[y][x + 1] == 0 || maze[y][x - 1] == 0)
		{
			return 1;
		}
		break;
	default:
		return 0;
	}
	return 0;
}

uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y)
{
	uint8_t x_in_bounds = x >= PATHFINDING_STARTING_INDEX && x < PATHFINDING_MAZE_WIDTH;
	uint8_t y_in_bounds = y >= PATHFINDING_STARTING_INDEX && y < PATHFINDING_MAZE_HEIGHT;

	return x_in_bounds && y_in_bounds;
}
