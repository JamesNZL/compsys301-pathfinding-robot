#include "pathfinding.h"

const static int8_t dY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t dX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

Queue *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t[][] maze)
{
	Queue *q = Queue_construct();
	Queue_append(Pathfinding_create_node(start));

	while (!Queue_is_empty(q))
	{
		Node *current = Queue_pop(q);
		Point *point = current->value;
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX;
			uint8_t newY;
		}
	}
}

Node *Pathfinding_create_node(Point *point)
{
	return Node_create(point);
}

bool Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y)
{
	bool x_in_bounds = x >= PATHFINDING_STARTING_INDEX && x < PATHFINDING_MAZE_WIDTH;
	bool y_in_bounds = y >= PATHFINDING_STARTING_INDEX && y < PATHFINDING_MAZE_HEIGHT;

	return x_in_bounds && y_in_bounds;
}
