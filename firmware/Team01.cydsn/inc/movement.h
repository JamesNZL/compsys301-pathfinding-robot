#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "sensor.h"

#include <cytypes.h>

/*
 * Debugging
 */
#define MOVEMENT_DEBUG_SKEW
// #define MOVEMENT_DEBUG_TURNS

/*
 * Motor Control Register
 */
#define MOTOR_LEFT_CR_POS	 0
#define MOTOR_RIGHT_CR_POS	 1
#define MOTOR_DISABLE_CR_POS 2

#define MOVEMENT_DISABLE	 Motor_Control_Reg_Write(Motor_Control_Reg_Read() | (1 << MOTOR_DISABLE_CR_POS))
#define MOVEMENT_ENABLE		 Motor_Control_Reg_Write(Motor_Control_Reg_Read() & ~(1 << MOTOR_DISABLE_CR_POS))

/*
 * Robot Physical Constants
 */
#define MOVEMENT_PIVOT_CIRCUMFERENCE 354.277f
#define MOVEMENT_WHEEL_CIRCUMFERENCE 203.57f
#define MOVEMENT_PULSE_REVOLUTION	 228
#define MOVEMENT_PULSE_90_DEGREE	 99
#define MOVEMENT_PULSE_180_DEGREE	 200

#define MOVEMENT_MM_PER_PULSE		 0.8928f
#define MOVEMENT_CM_CONVERSION		 11.20072f

/*
 * Calibrations
 */

/* Speeds */
#define MOVEMENT_SPEED_OFF	 0
#define MOVEMENT_SPEED_BRAKE 110 // ! no lower than 110
#define MOVEMENT_SPEED_SLOW	 120 // ! no lower than 110
#define MOVEMENT_SPEED_RUN	 180 // ! no lower than 130, no more than 240, 160 & 180 are KNOWN GOOD
#define MOVEMENT_SPEED_TURN	 130

/* Skew */
/** @brief Percentage of the current speed by which to correct skew. */
#define MOVEMENT_SKEW_CORRECTION_FACTOR 10
/** @brief Percentage of the current speed by which to boost skew correction. */
#define MOVEMENT_SKEW_BOOST_FACTOR 4

/* Turns */
#define MOVEMENT_TURNS_CORRECTION		 -3 // more negative -> more turn
#define MOVEMENT_TURNS_LEFT_CORRECTION	 25 // more positive -> less turn
#define MOVEMENT_TURNS_RIGHT_CORRECTION	 25 // more positive -> less turn

#define MOVEMENT_TURNS_STATIC_PERIOD	 100 // in ms

#define MOVEMENT_TURNS_REFRACTORY_PULSES 60

/* Sweeps */
/** @brief Percentage of the previous pulse count to add to the maximum allowed pulses before overruling predicate */
#define MOVEMENT_SWEEP_OVERSHOOT_FACTOR 50

/**
 * @brief The possible movement directions for the robot.
 */
typedef enum Direction
{
	DIRECTION_FORWARD,
	DIRECTION_REVERSE,
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
} Direction;

/**
 * @brief Initialises all movement dependencies
 */
void Movement_init_motors(void);

/**
 * @brief Converts cm per second to pulses per second
 *
 * @param cms the centimeters per second to target
 */
uint16 Movement_cm_to_pulse(float cm);
/**
 * @brief Instructs the robot to move a certain number of mm
 *
 * @param distance the distance to move in mm
 */
void Movement_move_mm(uint16 distance);

/**
 * @brief Checks if there is distance to move - sets speed accordingly
 */
void Movement_check_distance(void);

/**
 * @brief Executes the next control loop cycle with feedback
 */
void Movement_next_control_cycle(void);

/**
 * @brief Resets both motor speeds in cm/s - to be called after skew corrected alignment is met
 */
void Movement_sync_motors(uint16 speed);

/**
 * @brief Corrects the skew of the robot
 *
 * @param direction the direction to turn faster in to correct a skew
 * @param boostFactor the percentage of the current speed by which to boost skew correction
 */
void Movement_skew_correct(Direction direction, int8 boostFactor);

/**
 * @brief Check if the previous turn is complete and re-enable turn sensors if so
 */
void Movement_check_turn_complete(void);

/**
 * @brief Turns the robot left (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn left from the current position
 */
void Movement_turn_left(uint16 angle);

/**
 * @brief Sweep the motor left and right and determine the next action.
 *
 * @param resetHeading Whether the reset the heading once the shortest sweep is found.
 * @return SensorActions The next action to take to return to a valid state.
 */
SensorActions Movement_sweep(bool resetHeading);

/**
 * @brief Turns the robot right (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn right from the current position
 */
void Movement_turn_right(uint16 angle);

/**
 * @brief Writes the motor pulse target physically
 *
 * @param target The target amount of pulses for a motor to turn in one second
 */
void Movement_write_M1_pulse(uint16 target);
void Movement_write_M2_pulse(uint16 target);

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
void Movement_set_speed(uint8 percent);
void Movement_set_speed_right(uint8 percent);
void Movement_set_speed_left(uint8 percent);

#endif
