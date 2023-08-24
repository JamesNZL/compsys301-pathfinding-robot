#include "pathfinding.h"

const static int8_t dY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t dX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

Queue *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	Queue *q = Queue_construct();
	Queue_append(Pathfinding_create_node(start));

	while (!Queue_is_empty(q))
	{
		uint8_t visited[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH];
		Node *current = Queue_pop(q);
		Point *point = current->value;
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX = point->x + dX[i];
			uint8_t newY = point->y + dY[i];
			if (Pathfinding_coordinates_in_bounds(newX, newY) && !visited[newY][newX])
			{
				Node *neighbour = Pathfinding_create_node(Point_create(newX, newY));
				visited[newY][newX] = TRUE;
				Queue_append(neighbour);
			}
		}
		Point_destroy(point);
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
