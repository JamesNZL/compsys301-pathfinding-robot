#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "sensor.h"

#include <cytypes.h>

/*
 * Debugging
 */
#define MOVEMENT_DEBUG_SKEW
// #define MOVEMENT_DEBUG_TURNS

// #define MOVEMENT_TURN_WITH_SENSORS

// #define MOVEMENT_PID_SKEW

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
#define MOVEMENT_PULSE_180_DEGREE	 198

#define MOVEMENT_MM_PER_PULSE		 0.8928f
#define MOVEMENT_CM_CONVERSION		 11.20072f

/*
 * Calibrations
 */

/* Distance */
#define MOVEMENT_MM_PULSE_CORRECTION 15

/* Speeds */
#define MOVEMENT_SPEED_OFF	 0
#define MOVEMENT_SPEED_BRAKE 115 // ! no lower than 115
#define MOVEMENT_SPEED_SLOW	 120 // ! no lower than 115
#define MOVEMENT_SPEED_RUN	 180 // ! no lower than 130, no more than 240, 160 & 180 are KNOWN GOOD
#define MOVEMENT_SPEED_TURN	 130

/* Skew */
/** @brief Percentage of the current speed by which to correct skew. */
#define MOVEMENT_SKEW_CORRECTION_FACTOR		  20
#define MOVEMENT_SKEW_NUMERIC_PULSES		  9
#define MOVEMENT_SKEW_NUMERIC_PULSES_SUPPRESS 5
#define MOVEMENT_SKEW_STABILITY_PULSE_TIMEOUT 280

/* Turns */
/** @brief Overshoot factor for turn angles before stopping sensor detection */
#ifdef MOVEMENT_TURN_WITH_SENSORS
#define MOVEMENT_TURNS_OVERSHOOT_FACTOR 20
#else
#define MOVEMENT_TURNS_OVERSHOOT_FACTOR 0
#endif
#define MOVEMENT_TURNS_CORRECTION		 -3 // more negative -> more turn
#define MOVEMENT_TURNS_LEFT_CORRECTION	 25 // more positive -> less turn
#define MOVEMENT_TURNS_RIGHT_CORRECTION	 25 // more positive -> less turn

#define MOVEMENT_TURNS_STATIC_PERIOD	 100 // in ms

#define MOVEMENT_TURNS_REFRACTORY_PULSES 60

/* Sweeps */
/** @brief Percentage of the previous pulse count to add to the maximum allowed pulses before overruling predicate */
#define MOVEMENT_SWEEP_OVERSHOOT_FACTOR 25

/* Recovery */
#define MOVEMENT_RECOVERY_DELAY_PERIOD 200

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
 */
void Movement_skew_correct(Direction direction);

/**
 * @brief Sets the variables leftSkewBoost and rightSkewBoost, which are used by Movement_write_M1_pulse
 *
 * @param left the numeric pulse increase to directly write to PWM1
 * @param right the numeric pulse increase to directly write to PWM2
 */
void Movement_set_direct_skew_boosts(uint8 left, uint8 right);

/**
 * @brief Copy of below - Waits until a specific turn timeout before suppressing skew correction
 */
void Movement_skew_stability_timeout(void);

/**
 * @brief Check if the previous turn is complete and re-enable turn sensors if so
 */
void Movement_check_turn_complete(void);
/**
 * @brief Turns the robot left (on the spot) by angle degrees
 *
 * @param maxAngle The maximum angle (in degrees) to turn left from the current position before aborting the predicate
 * @param predicate A predicate to test as the robot turns, halting once satisfied
 */
void Movement_turn_left(uint16 maxAngle, bool predicate(void));
/**
 * @brief Turns the robot right (on the spot) by angle degrees
 *
 * @param maxAngle The maximum angle (in degrees) to turn right from the current position before aborting the predicate
 * @param predicate A predicate to test as the robot turns, halting once satisfied
 */
void Movement_turn_right(uint16 maxAngle, bool predicate(void));

/**
 * @brief Sweep the motor left and right and determine the next action using a predicate.
 *
 * @param predicate A predicate to test as the robot is swept.
 * @param actionIfUnsatisfied The action to return if the predicate is not satisfied.
 * @param
 * @return SensorActions The next action to take to return to a valid state.
 */
SensorActions Movement_sweep(bool predicate(void), SensorActions actionIfUnsatisfied);

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
