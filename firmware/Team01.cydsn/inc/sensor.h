#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE			0
#define SENSOR_COUNT					7
#define SENSOR_DEFAULT_BIAS_VOLTAGE		1.1F
#define SENSOR_MINIMUM_DEBOUNCE_PERIODS 3
#define SENSOR_SAMPLING_PERIODS			10

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

void Sensor_write_statuses_to_debug();

void Sensor_process_sensor_statuses();

void Sensor_reset_counts(Sensor sensorStruct);

bool Sensor_all_sensors_off();

#endif