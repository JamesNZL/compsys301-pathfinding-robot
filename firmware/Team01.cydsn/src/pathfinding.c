#include "pathfinding.h"

const static int8_t DY[PATHFINDING_POSSIBLE_DIRECTIONS] = { 0, 0, -1, 1 };
const static int8_t DX[PATHFINDING_POSSIBLE_DIRECTIONS] = { -1, 1, 0, 0 };

/* Everything relating to the route data structure*/
typedef struct PathfindingRoute
{
	Queue *actions;
	MazeDirections lastFacedDirection;
	uint8_t finalDistance;
} PathfindingRoute;

PathfindingRoute *Pathfinding_route_construct(Queue *actions, MazeDirections lastFacedDirection, uint8_t finalDistance)
{
	PathfindingRoute *route = malloc(sizeof(PathfindingRoute));
	if (route == NULL)
	{
		return NULL;
	}
	route->actions = actions;
	route->lastFacedDirection = lastFacedDirection;
	route->finalDistance = finalDistance;
	return route;
}

void Pathfinding_route_destroy(PathfindingRoute *route)
{
	if (route == NULL)
	{
		return;
	}
	free(route);
}

Queue *Pathfinding_route_get_actions(PathfindingRoute *route)
{
	return route->actions;
}

MazeDirections Pathfinding_route_get_last_faced_direction(PathfindingRoute *route)
{
	return route->lastFacedDirection;
}

uint8_t Pathfinding_route_get_final_distance(PathfindingRoute *route)
{
	return route->finalDistance;
}

/* END route operations */

Queue *Pathfinding_generate_routes_to_all_food(Point *start, MazeDirections startingDirection, uint8_t foodLocations[PATHFINDING_TOTAL_FOOD_LOCATIONS][2], uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	Queue *routes = Queue_construct();
	Point *currentStartPoint = start;
	MazeDirections currentStartingDirection = startingDirection;
	for (uint8_t i = 0; i < PATHFINDING_TOTAL_FOOD_LOCATIONS; ++i)
	{
		uint8_t *currentFoodLocation = foodLocations[i];
		Point *currentEndPoint = Point_create(currentFoodLocation[0], currentFoodLocation[1], PATHFINDING_MAZE_WIDTH);
		Stack *currentShortestPath = Pathfinding_find_shortest_path_bfs(currentStartPoint, currentEndPoint, maze);
		PathfindingRoute *currentRoute = Pathfinding_generate_route_to_food(currentShortestPath, currentStartingDirection, maze);
		Queue_append(routes, Node_create(currentRoute));

		currentStartPoint = currentEndPoint;
		currentStartingDirection = Pathfinding_route_get_last_faced_direction(currentRoute);
	}

	return routes;
}

void Pathfinding_check_if_waiting_for_final_action_in_queue(Queue *actions)
{
#ifndef TESTING
	if (Queue_is_empty(actions) && FLAG_IS_CLEARED(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE))
	{
		FLAG_SET(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE);
	}
	else if (Queue_is_empty(actions))
	{
		FLAG_CLEAR(FLAGS, FLAG_WAITING_FOR_FINAL_ACTION_IN_QUEUE);
	}
#endif
}

uint8_t Pathfinding_is_moving_horizontally(MazeDirections directionOfMotion)
{
	switch (directionOfMotion)
	{
	case MAZE_DIRECTIONS_LEFT:
	case MAZE_DIRECTIONS_RIGHT:
		return 1;
	default:
		return 0;
	}
}
uint8_t Pathfinding_is_moving_vertically(MazeDirections directionOfMotion)
{
	switch (directionOfMotion)
	{
	case MAZE_DIRECTIONS_UP:
	case MAZE_DIRECTIONS_DOWN:
		return 1;
	default:
		return 0;
	}
}

Stack *Pathfinding_find_shortest_path_bfs(Point *start, Point *end, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	// predecessor array to store shortest path
	uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH];
	for (int i = 0; i < PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH; ++i)
	{
		pred[i] = UINT16_MAX; // initialize to "no predecessor"
	}

	uint8_t visited[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH] = { 0 };
	visited[Point_get_y(start)][Point_get_x(start)] = 1;
	Queue *q = Queue_construct();
	Queue_append(q, Node_create(start));
	Point *currentPoint;
	while (!Queue_is_empty(q))
	{
		Node *currentNode = Queue_pop(q);
		currentPoint = Node_get_value(currentNode);
		// printf("(%i,%i)", Point_get_x(current_point), Point_get_y(current_point));
		if (Point_equal(currentPoint, end))
		{
			Node_destroy(currentNode);
			break;
		}
		for (uint8_t i = 0; i < PATHFINDING_POSSIBLE_DIRECTIONS; ++i)
		{
			uint8_t newX = Point_get_x(currentPoint) + DX[i];
			uint8_t newY = Point_get_y(currentPoint) + DY[i];
			if ((Pathfinding_coordinates_in_bounds(newX, newY)) && (!visited[newY][newX]) && (maze[newY][newX] == 0))
			{
				Point *neighbourPoint = Point_create(newX, newY, PATHFINDING_MAZE_WIDTH);
				Node *neighbour = Node_create(neighbourPoint);
				pred[Point_get_1d(neighbourPoint)] = Point_get_1d(currentPoint);
				visited[newY][newX] = 1;
				Queue_append(q, neighbour);
			}
		}
		Node_destroy(currentNode);
		// we can't destroy the reference to the start point
		if (!Point_equal(start, currentPoint))
		{
			Point_destroy(currentPoint);
		}
	}
	Stack *stack = Stack_construct();
	Pathfinding_build_stack_from_pred(stack, pred, start, end);
	Queue_destroy(q);
	return stack;
}

PathfindingRoute *Pathfinding_generate_route_to_food(Stack *shortestPath, MazeDirections startingDirection, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	MazeDirections currentDirection = startingDirection;
	Queue *actions = Queue_construct();
	Point *lastIntersectionPoint = NULL;
	uint8_t finalDistance;

	Node *currentNode = Stack_peek(shortestPath);
	Point *currentPoint = Node_get_value(currentNode);

	uint8_t startX = Point_get_x(currentPoint);
	uint8_t startY = Point_get_y(currentPoint);

	while (!Stack_is_empty(shortestPath))
	{
		currentNode = Stack_pop(shortestPath);
		currentPoint = Node_get_value(currentNode);
		Node_destroy(currentNode);

		uint8_t currentX = Point_get_x(currentPoint);
		uint8_t currentY = Point_get_y(currentPoint);

		// we popped the last node
		if (Stack_is_empty(shortestPath))
		{
			if (lastIntersectionPoint == NULL)
			{
				finalDistance = Pathfinding_calculate_point_spacing(currentDirection, Point_create(startX, startY, PATHFINDING_MAZE_WIDTH), currentPoint);
			}
			else
			{
				// printf("final: (%i,%i), last: (%i,%i)", Point_get_x(current_point), Point_get_y(current_point), Point_get_x(last_intersection_point), Point_get_y(last_intersection_point));
				finalDistance = Pathfinding_calculate_point_spacing(currentDirection, currentPoint, lastIntersectionPoint);
				Point_destroy(lastIntersectionPoint);
			}
			Stack_destroy(shortestPath);
			Point_destroy(currentPoint);
			break;
		}

		// dont destroy node here becauase we pop it next iteration
		Node *next_node = Stack_peek(shortestPath);
		Point *next_point = Node_get_value(next_node);

		MazeDirections relativeDirectionOfNext = Pathfinding_get_relative_direction(currentPoint, next_point);
		Actions requiredAction = Pathfinding_get_required_action(currentDirection, relativeDirectionOfNext);
		// Need a pointer to use node
		Actions *requiredActionPointer = malloc(sizeof(Actions));

		currentDirection = relativeDirectionOfNext;

		if (requiredAction == ACTIONS_STRAIGHT)
		{
			if (Pathfinding_is_on_intersection(currentDirection, currentX, currentY, maze))
			{
				lastIntersectionPoint = currentPoint;
				*requiredActionPointer = ACTIONS_SKIP;
				Queue_append(actions, Node_create(requiredActionPointer));
			}
			else
			{
				free(requiredActionPointer);
				// no longer need point if its not part of an intersection
				Point_destroy(currentPoint);
			}
		}
		else
		{
			lastIntersectionPoint = currentPoint;
			*requiredActionPointer = requiredAction;
			Queue_append(actions, Node_create(requiredActionPointer));
		}
	}

	// we add 1 to the final distance to be inclusive of the last intersection point
	PathfindingRoute *route = Pathfinding_route_construct(actions, currentDirection, finalDistance + 1);
	return route;
}

void Pathfinding_build_stack_from_pred(Stack *stack, uint16_t pred[PATHFINDING_MAZE_HEIGHT * PATHFINDING_MAZE_WIDTH], Point *start, Point *end)
{
	if (Point_equal(start, end))
	{
		// create copy of start node to avoid double free
		Point *startNodeCopy = Point_create(Point_get_x(start), Point_get_y(start), PATHFINDING_MAZE_WIDTH);
		Stack_push(stack, Node_create(startNodeCopy));
		return;
	}
	// start with final point
	uint16_t currentIndex = Point_get_1d(end);
	// use starting point to know if we've reached the end
	uint16_t startIndex = Point_get_1d(start);
	while ((currentIndex != UINT16_MAX) && (currentIndex != startIndex))
	{
		// printf("%i\n", current_index);
		Node *currentNode = Node_create(Point_create_from_1d(currentIndex, PATHFINDING_MAZE_WIDTH));
		Stack_push(stack, currentNode);
		currentIndex = pred[currentIndex];
	}
	// push the start node
	if (currentIndex == startIndex)
	{
		Node *startNode = Node_create(Point_create_from_1d(startIndex, PATHFINDING_MAZE_WIDTH));
		Stack_push(stack, startNode);
	}
}

MazeDirections Pathfinding_get_relative_direction(Point *current, Point *next)
{
	uint8_t currentX = Point_get_x(current);
	uint8_t currentY = Point_get_y(current);
	uint8_t nextX = Point_get_x(next);
	uint8_t nextY = Point_get_y(next);

	// TODO: possible handle non-adjacent cases i.e throw error
	// is in a different X position
	if (currentX != nextX)
	{
		// next is on the left
		if (nextX < currentX)
		{
			return MAZE_DIRECTIONS_LEFT;
		}
		else
		{
			return MAZE_DIRECTIONS_RIGHT;
		}
	}
	else
	{
		// y is different
		if (nextY < currentY)
		{
			// next is above
			return MAZE_DIRECTIONS_UP;
		}
		else
		{
			return MAZE_DIRECTIONS_DOWN;
		}
	}
}
Actions Pathfinding_get_required_action(MazeDirections current, MazeDirections next)
{
	switch (current)
	{
	case MAZE_DIRECTIONS_LEFT:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_LEFT;
		}
		break;
	}
	case MAZE_DIRECTIONS_RIGHT:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_RIGHT;
		}
		break;
	}
	case MAZE_DIRECTIONS_UP:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_STRAIGHT;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_AROUND;
		}
		break;
	}
	case MAZE_DIRECTIONS_DOWN:
	{
		switch (next)
		{
		case MAZE_DIRECTIONS_LEFT:
			return ACTIONS_RIGHT;
		case MAZE_DIRECTIONS_RIGHT:
			return ACTIONS_LEFT;
		case MAZE_DIRECTIONS_UP:
			return ACTIONS_AROUND;
		case MAZE_DIRECTIONS_DOWN:
			return ACTIONS_STRAIGHT;
		}
		break;
	}
	}
	return ACTIONS_SKIP;
}

uint8_t Pathfinding_calculate_point_spacing(MazeDirections currentDirection, Point *point_1, Point *point_2)
{

	if (Pathfinding_is_moving_horizontally(currentDirection))
	{
		// implement abs manually
		return abs(Point_get_x(point_1) - Point_get_x(point_2));
	}
	else if (Pathfinding_is_moving_vertically(currentDirection))
	{

		return abs(Point_get_y(point_1) - Point_get_y(point_2));
	}
	return 0;
}

uint8_t Pathfinding_is_on_intersection(MazeDirections currentDirection, uint8_t x, uint8_t y, uint8_t maze[PATHFINDING_MAZE_HEIGHT][PATHFINDING_MAZE_WIDTH])
{
	if (Pathfinding_is_moving_horizontally(currentDirection))
	{
		if ((maze[y + 1][x] == 0) || (maze[y - 1][x] == 0))
		{
			return 1;
		}
	}
	else if (Pathfinding_is_moving_vertically(currentDirection))
	{
		if ((maze[y][x + 1] == 0) || (maze[y][x - 1] == 0))
		{
			return 1;
		}
	}

	return 0;
}

uint8_t Pathfinding_coordinates_in_bounds(uint8_t x, uint8_t y)
{
	uint8_t xInBounds = (x >= PATHFINDING_STARTING_INDEX) && (x < PATHFINDING_MAZE_WIDTH);
	uint8_t yInBounds = (y >= PATHFINDING_STARTING_INDEX) && (y < PATHFINDING_MAZE_HEIGHT);

	return xInBounds && yInBounds;
}
