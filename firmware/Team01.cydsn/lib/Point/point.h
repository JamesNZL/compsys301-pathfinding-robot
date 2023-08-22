#ifndef POINT_H_
#define POINT_H_

#include <stdint.h>

struct Point;

/// @brief Allocates memory for a point representing a point in the maze as (x,y)
/// @param x the x-coordinates (cols) ZERO INDEXED
/// @param y the y-coordinates (rows) ZERO INDEXED
/// @return
Point *Point_create(uint8_t x, uint8_t y);

/// @brief Frees the memory occupied by a point
/// @param point
/// @return
void *Point_destroy(*Point point);

#endif