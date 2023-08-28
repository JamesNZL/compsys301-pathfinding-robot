#include "test_pathfinding.h"
#include <assert.h>
#include <stdio.h>

int main()
{
	Point *start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Point *end = Point_create(17, 1, PATHFINDING_MAZE_WIDTH);
	Stack *path = Pathfinding_find_shortest_path_bfs(start, end, map);
	Node *first = Stack_peek(path);
	Point *value = Node_get_value(first);
	printf("First Node: (%i, %i) \n", Point_get_x(value), Point_get_y(value));
	return 0;
}