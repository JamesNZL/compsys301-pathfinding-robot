#ifndef PATHFINDING_H_
#define PATHFINDING_H_
#include "../lib/Node/Node.h"
#include "../lib/Point/Point.h"
#include "../lib/Queue/Queue.h"

#define PATHFINDING_MAZE_WIDTH			19
#define PATHFINDING_MAZE_HEIGHT			15
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

uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y);

Node *Pathfinding_create_node(Point *point);

Queue *
Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

#endif