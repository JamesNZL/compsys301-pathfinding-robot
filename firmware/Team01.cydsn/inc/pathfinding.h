#ifndef PATHFINDING_H_
#define PATHFINDING_H_
#include "../lib/Point/Point.h"
#include "../lib/Queue/Queue.h"
#include <stdbool.h>

#define PATHFINDING_MAZE_WIDTH			69
#define PATHFINDING_MAZE_HEIGH			69
#define PATHFINDING_STARTING_INDEX		0
#define PATHFINDING_POSSIBLE_DIRECTIONS 4

bool Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y);

Queue *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t[][] maze);

#endif