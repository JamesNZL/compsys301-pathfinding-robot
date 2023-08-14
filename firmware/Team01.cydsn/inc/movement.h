#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stddef.h>
#include <stdint.h>

#define MOTOR_LEFT_CR_POS  0
#define MOTOR_RIGHT_CR_POS 1

#define PWM_MAX			   255
#define PULSE_MAX_QUARTER  57

/**
 * @brief The possible movement directions for the robot.
 */
typedef enum Direction
{
	DIRECTION_FORWARD,
	DIRECTION_REVERSE,
} Direction;

// Movement variables

// Target pulse - Desired motor speed to reference in control loop
uint8_t TARGET_PULSE_L, TARGET_PULSE_R;
// Apparent pulse - Measured encoder pulses to compare to target
volatile uint8_t APPARENT_PULSE_L, APPARENT_PULSE_R, TOTAL_PULSE_L, TOTAL_PULSE_R;
volatile float PULSE_ERROR, CURRENT_PWM_L, CURRENT_PWM_R, correction, next_PWM;

/**
 * @brief Calls the necessary API routines to start control loop components
 */
void init_control_loop();

/**
 * @brief setters for target pulse
 *
 * @param target The target pulse count (1/4 of desired)
 */
void set_target_pulse_L(uint8_t target);
void set_target_pulse_R(uint8_t target);

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