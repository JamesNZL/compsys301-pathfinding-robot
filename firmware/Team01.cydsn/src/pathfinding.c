#include "pathfinding.h"

const static int8_t dY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t dX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

Stack *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	// predecessor array to store shortest path
	uint8_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH];
	Queue *q = Queue_construct();
	Queue_append(q, Pathfinding_create_node(start));
	while (!Queue_is_empty(q))
	{
		uint8_t visited[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH];
		Node *current = Queue_pop(q);
		Point *point = Node_get_value(current);
		if (Point_equal(point, end))
		{
			break;
		}
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX = Point_get_x(point) + dX[i];
			uint8_t newY = Point_get_y(point) + dY[i];
			if (Pathfinding_coordinates_in_bounds(newX, newY) && !visited[newY][newX])
			{
				Point *neighbour_point = Point_create(newX, newY, PATHFINDING_MAZE_WIDTH);
				Node *neighbour = Pathfinding_create_node(neighbour_point);
				pred[Point_get_1d(neighbour_point)] = Point_get_1d(point);
				visited[newY][newX] = 1;
				Queue_append(q, neighbour);
			}
		}
		Node_destroy(current);
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
