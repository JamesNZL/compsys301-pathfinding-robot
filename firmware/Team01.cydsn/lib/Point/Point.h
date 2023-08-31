#ifndef POINT_H_
#define POINT_H_

#include <stdint.h>

typedef struct Point Point;

/**
 * @brief Allocates memory for a point representing a location in the maze as (x, y).
 * @param x The x-coordinate (cols) - ZERO INDEXED
 * @param y The y-coordinate (rows) - ZERO INDEXED
 * @param COLUMNS The width of the maze in which the point resides
 * @return A pointer to the created Point
 */
Point *Point_create(uint8_t x, uint8_t y, uint8_t COLUMNS);

/**
 * @brief Allocates memory for a point representing a location in the maze as (x, y),
 *        given a zero-indexed 1D index.
 * @param index The 1D index (zero-indexed) of the point
 * @param COLUMNS The width of the maze in which the point resides
 * @return A pointer to the created Point
 */
Point *Point_create_from_1d(uint16_t index, uint8_t COLUMNS);

/**
 * @brief Frees the memory occupied by a point.
 * @param point The point to be destroyed
 */
void Point_destroy(Point *point);

/**
 * @brief Checks if two points are equal.
 * @param point1 The first point
 * @param point2 The second point
 * @return 1 (TRUE) if the points are equal, 0 (FALSE) otherwise
 */
uint8_t Point_equal(Point *point1, Point *point2);

/**
 * @brief Gets the x-coordinate of a point.
 * @param point The point
 * @return The x-coordinate of the point
 */
uint8_t Point_get_x(Point *point);

/**
 * @brief Gets the y-coordinate of a point.
 * @param point The point
 * @return The y-coordinate of the point
 */
uint8_t Point_get_y(Point *point);

/**
 * @brief Converts a 2D point to a zero-indexed 1D index based on the width of the maze.
 * @param point The point to convert
 * @return The corresponding 1D index
 */
uint16_t Point_get_1d(Point *point);

#endif
