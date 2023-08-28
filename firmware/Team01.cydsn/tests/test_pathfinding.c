#include "test_pathfinding.h"
#include <assert.h>
#include <stdio.h>

void teardown(Point *start, Point *end, Stack *path)
{
	Point_destroy(start);
	Point_destroy(end);
	Stack_destroy(path);
}

int main()
{
	Point *start;
	Point *end;
	Stack *path;
	int length;

	printf("Test 1 Started.\n");
	start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	end = Point_create(17, 1, PATHFINDING_MAZE_WIDTH);
	path = Pathfinding_find_shortest_path_bfs(start, end, map);
	// Print the path
	printf("The shortest path is: \n");
	length = 0;
	while (!Stack_is_empty(path))
	{
		length++;
		Node *current = Stack_pop(path);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
	}
	printf("Length of path is: %i \n", length);
	assert(length == 21);
	teardown(start, end, path);

	printf("Test 2 Started.\n");
	start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	end = Point_create(17, 13, PATHFINDING_MAZE_WIDTH);
	path = Pathfinding_find_shortest_path_bfs(start, end, map);
	// Print the path
	printf("The shortest path is: \n");
	length = 0;
	while (!Stack_is_empty(path))
	{
		length++;
		Node *current = Stack_pop(path);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
	}
	printf("Length of path is: %i \n", length);
	assert(length == 21);
	teardown(start, end, path);
	return 0;
}