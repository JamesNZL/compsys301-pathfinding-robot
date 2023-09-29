#ifndef SENSOR_H_
#define SENSOR_H_

#include "common.h"
#include <project.h>

// #define SENSOR_DEBUG

// #define SENSOR_ACTIONS_INVALID_KILL
// #define SENSOR_ACTIONS_RIGOROUS

#define SENSOR_HARDWARE_MODE					  0

#define SENSOR_COUNT							  7
#define SENSOR_DEFAULT_BIAS_VOLTAGE_VOLTS		  1.2f
#define SENSOR_MINIMUM_DEBOUNCE_PERIODS			  5 // How many periods the signal has to remain at a level to be considered a valid level change
#define SENSOR_SAMPLING_PERIODS					  1 // Amount of times to sample all the sensors after a rising edge
#define SENSOR_SAMPLING_TIMER_PERIOD			  25 // 250 us - Delay between each sensor sample on a rising edge
#define SENSOR_RISING_EDGE_MAX_DELAY_TIMER_PERIOD 1200 // 12 ms - The maximum time allowed after a rising edge before all sensors are assumed to be off

#define SENSOR_SKEW_MIDDLE_POSITION				  6
#define SENSOR_SKEW_FRONT_LEFT_POSITION			  5
#define SENSOR_SKEW_FRONT_RIGHT_POSITION		  4
#define SENSOR_SKEW_BACK_LEFT_POSITION			  3
#define SENSOR_SKEW_BACK_RIGHT_POSITION			  2
#define SENSOR_TURN_LEFT_POSITION				  1
#define SENSOR_TURN_RIGHT_POSITION				  0

#define SENSOR_DEFAULT_INITIALISATION \
	{                                 \
		.periodCount = 0,             \
		.highWasSampled = FALSE,      \
		.previousStatus = FALSE,      \
		.status = FALSE               \
	}

typedef struct Sensor Sensor;

typedef enum SensorActions
{
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_FIND_VALID_STATE
} SensorActions;

// TODO: do i want to skew if only the rear skews detect? and leave the front as continue-forwards?
static const SensorActions SENSOR_ACTION_LUT[128] = {
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT_GENTLY,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT_GENTLY,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_ANTICIPATE_TURN,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CORRECT_LEFT,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CONTINUE_PREVIOUS,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CORRECT_RIGHT,
	SENSOR_ACTION_CONTINUE_FORWARD,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
	SENSOR_ACTION_FIND_VALID_STATE,
};

volatile extern Sensor Sensor_turnLeft;
volatile extern Sensor Sensor_turnRight;
volatile extern Sensor Sensor_skewBackRight;
volatile extern Sensor Sensor_skewBackLeft;
volatile extern Sensor Sensor_skewFrontRight;
volatile extern Sensor Sensor_skewFrontLeft;
volatile extern Sensor Sensor_skewMiddle;

/**
 * @brief Init all sensor dependencies - DAC, Bias levels, interrupts
 */
void Sensor_init_sensors(void);

/**
 * @return required action based on current LUT state
 */
SensorActions Sensor_determine_action(void);

/**
 * @brief Sets the bias level of DAC Lower and Upper
 */
void Sensor_set_bias_level(float voltage);

/**
 * @brief Writes to DB LEDs the status for each sensor
 */
void Sensor_write_statuses_to_debug(void);

/*
 * Conditionals
 */

/**
 * @return true if all sensors are off (on black)
 */
bool Sensor_is_all_sensors_off(void);

/**
 * @return true if there is only a right turn available currently
 */
bool Sensor_is_on_right_turn_intersection(void);
/**
 * @return true if there is only a left turn available currently
 */
bool Sensor_is_on_left_turn_intersection(void);
/**
 * @return true if there is a left AND right turn currently available
 */
bool Sensor_is_on_all_turn_intersection(void);

/**
 * @return true if there is a left OR right turn currently avialable
 */
bool Sensor_has_turn(void);

bool Sensor_has_right_turn(void);
bool Sensor_has_left_turn(void);
/**
 * @return true if the middle sensor is on the line
 */
bool Sensor_is_middle_on_line(void);

/**
 * @return true if either front sensor is on the line
 */
bool Sensor_is_any_front_on_line(void);
/**
 * @return true if both front sensors are on the line
 */
bool Sensor_is_both_front_on_line(void);
/**
 * @return true if either back sensor is on the line
 */
bool Sensor_is_any_back_on_line(void);
/**
 * @return true if all skew sensors are on line
 */
bool Sensor_are_skew_diagonals_on_line(void);

#endif