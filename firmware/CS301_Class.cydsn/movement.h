#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @brief The possible movement directions for the robot.
 */
typedef enum Direction
{
    FORWARD,
    REVERSE,
} Direction;

// Turning

/**
 * @brief Turns the robot right (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn right from the current position
 */
void turn_left(uint8_t angle);

/**
 * @brief Turns the robot left (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn left from the current position
 */
void turn_right(uint8_t angle);

// Direction
void set_direction(Direction direction);

// Speed
void set_speed(uint8_t percent);
void set_speed_right(uint8_t percent);
void set_speed_left(uint8_t percent);

// Debug
int16_t get_speed_left();
int16_t get_speed_right();

#endif
