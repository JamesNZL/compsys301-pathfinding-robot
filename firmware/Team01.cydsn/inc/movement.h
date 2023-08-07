#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stddef.h>
#include <stdint.h>

#define MOTOR_LEFT_CR_POS  0
#define MOTOR_RIGHT_CR_POS 1

/**
 * @brief The possible movement directions for the robot.
 */
typedef enum Direction
{
	DIRECTION_FORWARD,
	DIRECTION_REVERSE,
} Direction;

//Movement variables

//Target pulse - Desired motor speed to reference in control loop
volatile int TARGET_PULSE_L, TARGET_PULSE_R;
//Actual pulse - Measured encoder pulses to compare to target
volatile int ACTUAL_PULSE_L, ACTUAL_PULSE_R;

/**
 * @brief Calls the necessary API routines to start control loop components
 */
void init_control_loop();

/**
 * @brief Turns the robot right (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn right from the current position
 */
void Movement_turn_left(uint8_t angle);

/**
 * @brief Turns the robot left (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn left from the current position
 */
void Movement_turn_right(uint8_t angle);

/**
 * @brief sets the direction of BOTH motors to forwards or reverse
 *
 * @param direction the direction to set the motors to
 */
void Movement_set_direction(Direction direction);
void Movement_set_direction_right(Direction direction);
void Movement_set_direction_left(Direction direction);

/**
 * @brief sets the direction of BOTH motors to a percentage of the max speed
 *
 * @param percent percentage (out of 100) to set the motors to
 */
void Movement_set_speed(uint8_t percent);
void Movement_set_speed_right(uint8_t percent);
void Movement_set_speed_left(uint8_t percent);

// Utils
void Movement_set_pwm_1_duty_cycle(uint8_t percent);
void Movement_set_pwm_2_duty_cycle(uint8_t percent);
uint8_t Movement_calculate_compare(uint8_t percent);

// Debug
int16_t Movement_get_speed_left();
int16_t Movement_get_speed_right();

#endif