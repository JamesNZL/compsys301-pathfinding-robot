#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#define LEFT_MOTOR_CR_POS 0
#define RIGHT_MOTOR_CR_POS 1

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

/**
 * @brief sets the direction of BOTH motors to forwards or reverse
 *
 * @param direction the direction to set the motors to
 */
void set_direction(Direction direction);
void set_direction_right(Direction direction);
void set_direction_left(Direction direction);

/**
 * @brief sets the direction of BOTH motors to a percentage of the max speed
 *
 * @param percent percentage (out of 100) to set the motors to
 */
void set_speed(uint8_t percent);
void set_speed_right(uint8_t percent);
void set_speed_left(uint8_t percent);

// Utils
void set_pwm_1_duty_cycle(uint8_t percent);
void set_pwm_2_duty_cycle(uint8_t percent);
uint8_t calculate_compare(uint8_t percent);

// Debug
int16_t get_speed_left();
int16_t get_speed_right();

#endif
