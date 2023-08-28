#include "test_pathfinding.h"
#include <assert.h>
#include <stdio.h>

int main()
{
	printf("Test Started.\n");
	Point *start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Point *end = Point_create(17, 1, PATHFINDING_MAZE_WIDTH);
	Stack *path = Pathfinding_find_shortest_path_bfs(start, end, map);
	// Print the path
	printf("The shortest path is: \n");
	while (!Stack_is_empty(path))
	{
		Node *current = Stack_pop(path);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
	}
	return 0;
}