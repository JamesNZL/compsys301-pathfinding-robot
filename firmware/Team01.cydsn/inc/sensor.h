#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE				 0
#define SENSOR_COUNT						 7
#define SENSOR_DEFAULT_BIAS_VOLTAGE			 1.1F
#define SENSOR_MINIMUM_DEBOUNCE_PERIODS		 4
#define SENSOR_SAMPLING_PERIODS				 10
#define SENSOR_SAMPLING_PERIOD_COMPARE		 10 // 100 us
#define SENSOR_RISING_EDGE_MAX_DELAY_COMPARE 2000 // 20 ms

#define SENSOR_DEFAULT_INITIALISATION                                                             \
	{                                                                                             \
		.lowCount = 0, .highCount = 0, .periodCount = 0, .previousStatus = FALSE, .status = FALSE \
	}

#define SENSOR_PROCESS_READING(sensorStruct, sensorReadFunction) \
	bool sensorStruct##Reading = sensorReadFunction();           \
	if (sensorStruct##Reading)                                   \
	{                                                            \
		sensorStruct.highCount++;                                \
	}                                                            \
	else                                                         \
	{                                                            \
		sensorStruct.lowCount++;                                 \
	}

#define SENSOR_UPDATE_STATUS(sensorStruct)                                                           \
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

void Sensor_write_low_all_sensors();

#endif