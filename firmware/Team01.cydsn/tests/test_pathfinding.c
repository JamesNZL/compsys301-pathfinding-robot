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
	int length;

	printf("==============================Shortest Path Tests ==============================\n");
	printf("Test 1 Started.\n");
	Point *start = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Point *end = Point_create(17, 1, PATHFINDING_MAZE_WIDTH);
	Stack *path = Pathfinding_find_shortest_path_bfs(start, end, map);
	// Print the path
	printf("The shortest path is: \n");
	length = 0;
	while (!Stack_is_empty(path))
	{
		length++;
		Node *current = Stack_pop(path);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
		Point_destroy(value);
		Node_destroy(current);
	}
	printf("Length of path is: %i \n", length);
	assert(length == 21);
	teardown(start, end, path);

	printf("Test 2 Started.\n");
	Point *start_2 = Point_create(1, 1, PATHFINDING_MAZE_WIDTH);
	Point *end_2 = Point_create(17, 13, PATHFINDING_MAZE_WIDTH);
	Stack *path_2 = Pathfinding_find_shortest_path_bfs(start_2, end_2, map);
	// Print the path
	printf("The shortest path is: \n");
	length = 0;
	while (!Stack_is_empty(path_2))
	{
		length++;
		Node *current = Stack_pop(path_2);
		Point *value = Node_get_value(current);
		printf("(%i, %i) \n", Point_get_x(value), Point_get_y(value));
		Point_destroy(value);
		Node_destroy(current);
	}
	printf("Length of path is: %i \n", length);
	assert(length == 29);
	teardown(start_2, end_2, path_2);
	printf("==============================Direction tests ==============================\n");
	// Should be around
	Actions action_1 = Pathfinding_get_required_action(MAZE_DIRECTIONS_DOWN, MAZE_DIRECTIONS_UP);
	assert(action_1 == ACTIONS_AROUND);
	// Should be left (down to ->)
	Actions action_2 = Pathfinding_get_required_action(MAZE_DIRECTIONS_DOWN, MAZE_DIRECTIONS_RIGHT);
	assert(action_2 == ACTIONS_LEFT);
	return 0;
}