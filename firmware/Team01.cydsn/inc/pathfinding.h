#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <Node/Node.h>
#include <Point/Point.h>
#include <Queue/Queue.h>
#include <Stack/Stack.h>
#include <stdint.h>
#include <stdlib.h>

#define PATHFINDING_MAZE_WIDTH			19
#define PATHFINDING_MAZE_HEIGHT			15
#define PATHFINDING_STARTING_INDEX		0
#define PATHFINDING_POSSIBLE_DIRECTIONS 4

typedef struct Pathfinding_route Pathfinding_route;

typedef enum Actions
{
	ACTIONS_LEFT,
	ACTIONS_RIGHT,
	ACTIONS_SKIP,
	ACTIONS_AROUND,
	ACTIONS_STRAIGHT
} Actions;

typedef enum Maze_Directions
{
	MAZE_DIRECTIONS_LEFT,
	MAZE_DIRECTIONS_RIGHT,
	MAZE_DIRECTIONS_UP,
	MAZE_DIRECTIONS_DOWN
} Maze_Directions;

/// @brief Determines if an x and y value BOTH fall within range of the maze coordinates
/// @param x horizontal position
/// @param y vertical position
/// @return `TRUE` or `FALSE`
uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y);

/// @brief Calculates the action needed based on the positional state of the robot in the maze
/// @param current the direction the robot is facing in the maze
/// @param next the relative direction of the next point
/// @return
Actions Pathfinding_get_required_action(Maze_Directions current, Maze_Directions next);

/// @brief Finds the relative direction `up,down,left,right` of a point in the maze based on a current point
/// @param current a pointer to the current Point
/// @param next a pointer to the Point who's relative position is to be determined
/// @return
Maze_Directions Pathfinding_get_relative_direction(Point *current, Point *next);

/// @brief Creates and returns a pointer to a route data structure which has a queue containing the required turns, and the required amount of distance to be travelled after the final turn
/// @param turns a Queue of turns defined as enums
/// @param last_faced_direction the direction the robot will be facing after reaching the food
/// @param final_distance the units (in terms of the maze grid) required to be travelled after the final turn
/// @return
Pathfinding_route *Pathfinding_route_construct(Queue *turns, Maze_Directions last_faced_direction, uint8_t final_distance);

Queue *Pathfinding_route_get_turns(Pathfinding_route *route);
Maze_Directions Pathfinding_route_get_last_faced_direction(Pathfinding_route *route);
uint8_t Pathfinding_route_get_final_distance(Pathfinding_route *route);

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
void Pathfinding_build_stack_from_pred(Stack *stack, uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH], Point *start, Point *end);

/// @brief Gives a path to the food containing the turns needed, as well as instructions after the final turn such as distance
/// @param path a stack of the nodes contained within the shortest path
/// @return
Pathfinding_route *Pathfinding_generate_route_to_food(Stack *shortest_path, Maze_Directions starting_direction, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/// @brief Determines based on the current coordinates and direction if the point is an intersection
/// @param current_direction the direction the robot is facing in the maze
/// @param x The x coordinates of the point
/// @param y The y coordinates of the point
/// @param maze the 2d maze
/// @return
uint8_t Pathfinding_is_on_intersection(Maze_Directions current_direction, uint8_t x, uint8_t y, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

uint8_t Pathfinding_calculate_point_spacing(Maze_Directions current_direction, Point *point_1, Point *point_2);

#endif