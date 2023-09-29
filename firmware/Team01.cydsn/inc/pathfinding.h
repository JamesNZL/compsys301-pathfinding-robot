/**
 * @file Pathfinding.h
 * @brief Header file for Pathfinding
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#define TESTING

#include <Node/Node.h>
#include <Point/Point.h>
#include <Queue/Queue.h>
#include <Stack/Stack.h>
#include <stdint.h>
#include <stdlib.h>

#define PATHFINDING_MAZE_WIDTH			  19
#define PATHFINDING_MAZE_HEIGHT			  15
#define PATHFINDING_STARTING_INDEX		  0
#define PATHFINDING_POSSIBLE_DIRECTIONS	  4
#define PATHFINDING_TOTAL_FOOD_LOCATIONS  5

#define PATHFINDING_X_GRID_SCALE_MM		  127.5
#define PATHFINDING_Y_GRID_SCALE_MM		  80
#define PATHFINDING_OVERSHOOT_REDUCTION_X 80
#define PATHFINDING_OVERSHOOT_REDUCTION_Y 70

#define PATHFINDING_START_X				  1
#define PATHFINDING_START_Y				  1
#define PATHFINDING_STARTING_DIRECTION	  MAZE_DIRECTIONS_RIGHT

/* For usage with Movement_move_mm */

// Usage: GRID_DISTANCE_LUT_MM_X[distance] where distance is grids - 1 (based on scale of 127.5mm)
static const uint16_t GRID_DISTANCE_LUT_MM_X[PATHFINDING_MAZE_WIDTH] = {
	0, 127, 255, 382, 510, 637, 765, 892, 1020, 1147, 1275, 1275, 1402, 1530, 1657, 1785, 1912, 2040, 2167
};

// Usage: GRID_DISTANCE_LUT_MM_Y[distance] where distance is grids - 1 (based on scale of 80mm)
static const uint16_t GRID_DISTANCE_LUT_MM_Y[PATHFINDING_MAZE_WIDTH] = {
	0, 80, 160, 240, 320, 400, 480, 560, 640, 720, 800, 880, 960, 1040, 1120, 1200, 1280, 1360, 1440
};

static uint8_t PATHFINDING_MAZE[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]
	= {
		  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		  { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
		  { 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
		  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
		  { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },
		  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1 },
		  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
		  { 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	  };

static uint8_t PATHFINDING_FOOD_LIST[PATHFINDING_TOTAL_FOOD_LOCATIONS][2]
	= {
		  { 1, 9 },
		  { 5, 5 },
		  { 7, 1 },
		  { 13, 5 },
		  { 9, 9 },
	  };

typedef struct PathfindingRoute PathfindingRoute;

typedef enum Actions
{
	ACTIONS_LEFT,
	ACTIONS_RIGHT,
	ACTIONS_SKIP,
	ACTIONS_AROUND,
	ACTIONS_STRAIGHT,
} Actions;

typedef enum MazeDirections
{
	MAZE_DIRECTIONS_LEFT,
	MAZE_DIRECTIONS_RIGHT,
	MAZE_DIRECTIONS_UP,
	MAZE_DIRECTIONS_DOWN,
} MazeDirections;

/**
 * @brief Generates a queue containing all the pathfinding routes based on the food list and maze given a starting point
 * @param start A pointer to a Point of the starting location
 * @param startingDirection the direction the robot starts facing
 * @param foodList A 2D array containing the coordinates of the food locations
 * @param maze A 2D array representing the maze
 * @warning It is the caller's responsibility to destroy the queue and routes
 * @return
 */
Queue *Pathfinding_generate_routes_to_all_food(Point *start, MazeDirections startingDirection, uint8_t food_list[PATHFINDING_TOTAL_FOOD_LOCATIONS][2], uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/**
 * @brief returns true if the robot is currently moving horizontally
 * @param directionOfMotion a MAZE_DIRECTION enum
 */
uint8_t Pathfinding_is_moving_horizontally(MazeDirections directionOfMotion);
/**
 * @brief returns true if the robot is currently moving vertically
 * @param directionOfMotion a MAZE_DIRECTION enum
 */
uint8_t Pathfinding_is_moving_vertically(MazeDirections directionOfMotion);

void Pathfinding_check_if_waiting_for_final_action(Queue *turns);

#ifdef TESTING
/**
 * @brief Creates and returns a pointer to a route data structure which has a queue containing the required turns, and the required amount of distance to be travelled after the final turn
 * @param turns a Queue of turns defined as enums
 * @param lastFacedDirection the direction the robot will be facing after reaching the food
 * @param finalDistance the units (in terms of the maze grid) required to be travelled after the final turn
 * @return Pathfinding_route* Pointer to the created Pathfinding_route
 */
PathfindingRoute *
Pathfinding_route_construct(Queue *turns, MazeDirections lastFacedDirection, uint8_t finalDistance);

/**
 * @brief Frees a memory allocated to a pathfinding route pointer
 * @param route
 */
void Pathfinding_route_destroy(PathfindingRoute *route);

/**
 * @brief
 * @param route
 * @return Queue* The queue of turns in the route
 */
Queue *Pathfinding_route_get_turns(PathfindingRoute *route);

/**
 * @brief
 * @param route
 * @return Maze_Directions The last faced direction in the route
 */
MazeDirections Pathfinding_route_get_last_faced_direction(PathfindingRoute *route);

/**
 * @brief
 * @param route
 * @return uint8_t The final distance in the route
 */
uint8_t Pathfinding_route_get_final_distance(PathfindingRoute *route);

/**
 * @brief Determines if an x and y value BOTH fall within range of the maze coordinates
 * @param x horizontal position
 * @param y vertical position
 * @return `TRUE` or `FALSE`
 */
uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y);

/**
 * @brief Calculates the action needed based on the positional state of the robot in the maze
 * @param current the direction the robot is facing in the maze
 * @param next the relative direction of the next point
 * @return Actions The required action
 */
Actions Pathfinding_get_required_action(MazeDirections current, MazeDirections next);

/**
 * @brief Finds the relative direction `up,down,left,right` of a point in the maze based on a current point
 * @param current a pointer to the current Point
 * @param next a pointer to the Point whose relative position is to be determined
 * @return Maze_Directions The relative direction of the next point
 */
MazeDirections Pathfinding_get_relative_direction(Point *current, Point *next);

/**
 * @brief Returns a stack of points to represent the shortest path, with the top of the stack being the first node
 * @param start A Point representing the starting position in the maze
 * @param end A Point representing the destination position of the maze
 * @param maze 2D array representing the maze
 * @return Stack* Stack of points representing the shortest path
 * @warning it is the caller's responsibility to destroy the start and end points
 */
Stack *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/**
 * @brief Modifies a stack reference using a pred array to construct the shortest path stack
 * @param stack Reference to stack to be modified
 * @param pred The predecessor array
 * @param start A Point representing the starting position in the maze
 * @param end A Point representing the destination position of the maze
 * @warning it is the caller's responsibility to destroy the stack (this function does not free anything)
 */
void Pathfinding_build_stack_from_pred(Stack *stack, uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH], Point *start, Point *end);

/**
 * @brief Gives a path to the food containing the turns needed, as well as instructions after the final turn such as distance
 * @param path a stack of the nodes contained within the shortest path
 * @return Pathfinding_route* Pointer to the created Pathfinding_route
 * @warning DO NOT destroy the stack afterwards as this function does it (you will get DOUBLE FREE error)
 */
PathfindingRoute *Pathfinding_generate_route_to_food(Stack *shortestPath, MazeDirections startingDirection, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/**
 * @brief Determines based on the current coordinates and direction if the point is an intersection
 * @param currentDirection the direction the robot is facing in the maze
 * @param x The x coordinates of the point
 * @param y The y coordinates of the point
 * @param maze the 2d maze
 * @return uint8_t `TRUE` or `FALSE`
 */
uint8_t Pathfinding_is_on_intersection(MazeDirections currentDirection, uint8_t x, uint8_t y, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH]);

/**
 * @brief Calculates the spacing between two points based on current direction
 * @param currentDirection the direction the robot is facing in the maze
 * @param point1 The first point
 * @param point2 The second point
 * @return uint8_t The spacing between the two points
 */
uint8_t Pathfinding_calculate_point_spacing(MazeDirections currentDirection, Point *point1, Point *point2);

#endif
#endif
