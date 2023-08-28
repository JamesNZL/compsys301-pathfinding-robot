#include "test_pathfinding.h"
#include <assert.h>
#include <stdio.h>

int main()
{
	printf("Test 1 Started.\n");
	Point *start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Point *end = Point_create(17, 1, PATHFINDING_MAZE_WIDTH);
	Stack *path = Pathfinding_find_shortest_path_bfs(start, end, map);
	// Print the path
	printf("The shortest path is: \n");
	int length = 0;
	while (!Stack_is_empty(path))
	{
		length++;
		Node *current = Stack_pop(path);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
	}
	printf("Length of path is: %i \n", length);
	assert(length == 21);

	printf("Test 2 Started.\n");
	return 0;
}