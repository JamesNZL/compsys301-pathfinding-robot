#ifndef POINT_H_
#define POINT_H_

#include <stdint.h>

struct Point;

/// @brief
/// @param x
/// @param y
/// @return
Point *Point_create(uint8_t x, uint8_t y);

/// @brief
/// @param point
/// @return
void *Point_destroy(*Point point);

#endif