#ifndef POINT_H_
#define POINT_H_

#include <stdint.h>

typedef struct Point Point;

/// @brief Allocates memory for a point representing a point in the maze as (x,y)
/// @param x the x-coordinates (cols) ZERO INDEXED
/// @param y the y-coordinates (rows) ZERO INDEXED
/// @param COLUMNS the width of the maze which the point resides
/// @return
Point *Point_create(uint8_t x, uint8_t y, uint8_t COLUMNS);

/// @brief Frees the memory occupied by a point
/// @param point
/// @return
void Point_destroy(Point *point);

uint8_t Point_get_x(Point *point);
uint8_t Point_get_y(Point *point);
#endif