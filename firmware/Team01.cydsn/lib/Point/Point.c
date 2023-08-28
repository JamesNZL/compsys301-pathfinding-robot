#include "Point.h"
#include <stdlib.h>

typedef struct Point
{
	uint8_t x;
	uint8_t y;
	uint16_t one_dim_index;
} Point;

Point *Point_create(uint8_t x, uint8_t y, uint8_t COLUMNS)
{
	Point *point = malloc(sizeof(Point));
	if (point == NULL)
	{
		return NULL;
	}

	point->x = x;
	point->y = y;
	point->one_dim_index = x + y * COLUMNS;
	return point;
}

Point *Point_create_from_1d(uint16_t index, uint8_t COLUMNS)
{

	Point *point = malloc(sizeof(Point));
	if (point == NULL)
	{
		return NULL;
	}

	point->x = index % COLUMNS;
	point->y = index / COLUMNS;
	point->one_dim_index = index;
	return point;
}

void Point_destroy(Point *point)
{
	free(point);
}

uint8_t Point_equal(Point *point_1, Point *point_2)
{
	uint8_t x_equal = Point_get_x(point_1) == Point_get_x(point_2);
	uint8_t y_equal = Point_get_y(point_1) == Point_get_y(point_2);
	return x_equal && y_equal;
}

uint8_t Point_get_x(Point *point)
{
	return point->x;
}

uint8_t Point_get_y(Point *point)
{
	return point->y;
}