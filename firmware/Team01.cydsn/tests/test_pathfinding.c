#include "test_pathfinding.h"

int main()
{
	Point *start = Point_create(1, 1);
	Point *end = Point_create(17, 1);
	Pathfinding_find_shortest_path_bfs(start, end, map);
	return 0;
}