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
	if (point == NULL)
	{
		return;
	}
	free(point);
}

uint8_t Point_equal(Point *point_1, Point *point_2)
{
	return Point_get_1d(point_1) == Point_get_1d(point_2);
}

uint8_t Point_get_x(Point *point)
{
	return point->x;
}

uint8_t Point_get_y(Point *point)
{
	return point->y;
}
uint16_t Point_get_1d(Point *point)
{
	return point->one_dim_index;
}