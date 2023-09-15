#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE				 0
#define SENSOR_COUNT						 7
#define SENSOR_DEFAULT_BIAS_VOLTAGE_VOLTS	 1.5F
#define SENSOR_MINIMUM_DEBOUNCE_PERIODS		 4 // How many periods the signal has to remain at a level to be considered a valid level change
#define SENSOR_SAMPLING_PERIODS				 10 // Amount of times to sample all the sensors after a rising edge
#define SENSOR_SAMPLING_PERIOD_COMPARE		 10 // 100 us - Delay between each sensor sample on a rising edge
#define SENSOR_RISING_EDGE_MAX_DELAY_COMPARE 1200 // 20 ms - The maximum time allowed after a rising edge before all sensors are assumed to be off

#define SENSOR_DEFAULT_INITIALISATION                                                             \
	{                                                                                             \
		.lowCount = 0, .highCount = 0, .periodCount = 0, .previousStatus = FALSE, .status = FALSE \
	}

// Samples the sensor information and stores it for later processing
#define SENSOR_SAMPLE_READING(sensorStruct, sensorReadFunction) \
	bool sensorStruct##Reading = sensorReadFunction();          \
	if (sensorStruct##Reading)                                  \
	{                                                           \
		sensorStruct.highCount++;                               \
	}                                                           \
	else                                                        \
	{                                                           \
		sensorStruct.lowCount++;                                \
	}

// Debounces (ensures the signal has held its value for at least X periods) and stores the required status
#define SENSOR_DEBOUNCE_AND_UPDATE_STATUS(sensorStruct)                                              \
	sensorStruct.periodCount++;                                                                      \
	bool sensorStruct##newStatus = (sensorStruct.highCount >= sensorStruct.lowCount) ? TRUE : FALSE; \
	if (sensorStruct.previousStatus != sensorStruct##newStatus)                                      \
	{                                                                                                \
		sensorStruct.periodCount = 0;                                                                \
	}                                                                                                \
	if (sensorStruct.periodCount >= SENSOR_MINIMUM_DEBOUNCE_PERIODS)                                 \
	{                                                                                                \
		sensorStruct.status = sensorStruct##newStatus;                                               \
	}                                                                                                \
	sensorStruct.highCount = 0;                                                                      \
	sensorStruct.lowCount = 0;                                                                       \
	sensorStruct.previousStatus = sensorStruct##newStatus;

#define SENSOR_WRITE_LOW(sensorStruct) \
	sensorStruct.status = FALSE

#define SENSOR_WRITE_HIGH(sensorStruct) \
	sensorStruct.status = TRUE

#include "common.h"
#include <project.h>

typedef struct Sensor
{
	bool status;
	bool previousStatus;
	uint8 lowCount;
	uint8 highCount;
	uint8 periodCount;
} Sensor;

volatile extern Sensor Sensor_turnLeft;
volatile extern Sensor Sensor_turnRight;
volatile extern Sensor Sensor_skewBackRight;
volatile extern Sensor Sensor_skewBackLeft;
volatile extern Sensor Sensor_skewFrontRight;
volatile extern Sensor Sensor_skewFrontLeft;
volatile extern Sensor Sensor_skewCenter;

/**
 * @brief Init all sensor dependencies - DAC, Bias levels, interrupts
 */
void Sensor_init_sensors();

/**
 * @brief Stores the status of all sensors by reading their pins
 */
void Sensor_store_sensor_statuses();

/**
 * @brief Sets the bias level of DAC Lower and Upper
 */
void Sensor_set_bias_level(float voltage);

/**
 * @brief Writes to DB LEDs the status for each sensor
 */
void Sensor_write_statuses_to_debug();

/**
 * @brief read and count occurences of sensor statuses
 */
void Sensor_sample_sensor_readings();

// Conditional Statements

/**
 * @return true if all sensors are off (on black)
 */
bool Sensor_all_sensors_off();

/**
 * @return true if there is only a right turn available currently
 */
bool Sensor_on_right_turn_intersection();

/**
 * @return true if there is only a left turn available currently
 */
bool Sensor_on_left_turn_intersection();

/**
 * @return true if there is a left AND right turn currently available
 */
bool Sensor_on_all_turn_intersection();

/**
 * @return true if the robot is drifting (skewed) towards the right
 */
bool Sensor_is_right_skewed();

/**
 * @return true if the robot is drifting (skewed) towards the left
 */
bool Sensor_is_left_skewed();

/**
 * @brief sets the status of all sensor structs to FALSE (low)
 */
void Sensor_write_low_all_sensors();

/**
 * @brief Undertakes the required steps to reset and set the timer period
 * @param period a valid period for a 16-bit UDB timer
 */
void Sensor_set_light_check_timer_period(uint16 period);

#endif