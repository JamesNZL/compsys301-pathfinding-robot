#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE			0
#define SENSOR_COUNT					7
#define SENSOR_DEFAULT_BIAS_VOLTAGE		1.1F
#define SENSOR_MINIMUM_DEBOUNCE_PERIODS 2
#define SENSOR_DEFAULT_INITIALISATION                         \
	{                                                         \
		.counter = 0, .previousValue = FALSE, .status = FALSE \
	}

#define SENSOR_DEBOUNCE(sensorStruct, sensorReadFunction) \
	bool reading = sensorReadFunction();                  \
	if (sensorStruct.previousValue != reading)            \
	{                                                     \
		sensorStruct.counter = 0;                         \
	}                                                     \
	if (counter >= SENSOR_MINIMUM_DEBOUNCE_PERIODS)       \
	{                                                     \
		if (reading != sensorStruct.previousValue)        \
		{                                                 \
			sensorStruct.value = reading;                 \
		}                                                 \
	}                                                     \
	sensorStruct.previousValue = reading;

#include "common.h"
#include <project.h>

typedef struct Sensor
{
	bool status;
	bool previousValue;
	uint8 counter;
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

bool Sensor_all_sensors_off();

#endif