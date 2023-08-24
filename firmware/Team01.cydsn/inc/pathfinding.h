#ifndef PATHFINDING_H_
#define PATHFINDING_H_
#include "../lib/Node/Node.h"
#include "../lib/Point/Point.h"
#include "../lib/Queue/Queue.h"
#include "common.h"

#define PATHFINDING_MAZE_WIDTH			69
#define PATHFINDING_MAZE_HEIGHT			69
#define PATHFINDING_STARTING_INDEX		0
#define PATHFINDING_POSSIBLE_DIRECTIONS 4

typedef enum Actions
{
	ACTIONS_LEFT,
	ACTIONS_RIGHT,
	ACTIONS_SKIP,
	ACTIONS_AROUND,
	ACTIONS_ARRIVE
} Actions;

bool Pathfinding_coordinates_in_bounds(uint8 x, uint8 y);

Node *Pathfinding_create_node(Point *point);

Queue *
Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8[][] maze);

#endif