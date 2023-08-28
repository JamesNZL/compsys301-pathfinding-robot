#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <Node/Node.h>
#include <Point/Point.h>
#include <Queue/Queue.h>
#include <Stack/Stack.h>

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
/// @brief Returns a stack of points to represent the shortest path, with the top of the stack being the first node
/// @param start A Point representing the starting position in the maze
/// @param end  A Point represetning the destination position of the maze
/// @param maze 2D array representing the maze
/// @return
Stack *
Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/// @brief Modifies a stack reference using a pred array to construct the shortest path stack
/// @param stack Reference to stack to be modified
/// @param pred The predecessor array
/// @param start A Point representing the starting position in the maze
/// @param end  A Point represetning the destination position of the maze
/// @return
void *Pathfinding_build_stack_from_pred(Stack *stack, uint16_t[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH] pred, Point *start, Point *end);

#endif