#include "Point.h"
#include <stdlib.h>

struct Point
{
	uint8_t x;
	uint8_t y;
	uint16_t one_dim_index;
};

Point *Point_create(uint8_t x, uint8_t y)
{
	Point *point = malloc(sizeof(Point));
	if (point == NULL)
	{
		return NULL;
	}

	point->x = x;
	point->y = y;

	return point;
}

void Destroy_point(Point *point)
{
	free(point);
}