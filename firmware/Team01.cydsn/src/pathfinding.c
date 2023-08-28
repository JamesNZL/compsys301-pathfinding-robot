#include "pathfinding.h"

const static int8_t dY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t dX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

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
	Queue_append(q, Pathfinding_create_node(start));
	Point *current_point;
	while (!Queue_is_empty(q))
	{
		Node *current_node = Queue_pop(q);
		current_point = Node_get_value(current_node);
		// printf("(%i,%i)", Point_get_x(current_point), Point_get_y(current_point));
		if (Point_equal(current_point, end))
		{
			break;
		}
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX = Point_get_x(current_point) + dX[i];
			uint8_t newY = Point_get_y(current_point) + dY[i];
			if (Pathfinding_coordinates_in_bounds(newX, newY) && !visited[newY][newX] && maze[newY][newX] == 0)
			{
				Point *neighbour_point = Point_create(newX, newY, PATHFINDING_MAZE_WIDTH);
				Node *neighbour = Pathfinding_create_node(neighbour_point);
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

Node *Pathfinding_create_node(Point *point)
{
	return Node_create(point);
}

uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y)
{
	uint8_t x_in_bounds = x >= PATHFINDING_STARTING_INDEX && x < PATHFINDING_MAZE_WIDTH;
	uint8_t y_in_bounds = y >= PATHFINDING_STARTING_INDEX && y < PATHFINDING_MAZE_HEIGHT;

	return x_in_bounds && y_in_bounds;
}
