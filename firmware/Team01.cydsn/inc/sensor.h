#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE		0
#define SENSOR_COUNT				7
#define SENSOR_DEFAULT_BIAS_VOLTAGE 1.1F

#include "common.h"
#include <project.h>

volatile extern bool Sensor_turnLeft;
volatile extern bool Sensor_turnRight;
volatile extern bool Sensor_skewBackRight;
volatile extern bool Sensor_skewBackLeft;
volatile extern bool Sensor_skewFrontRight;
volatile extern bool Sensor_skewFrontLeft;
volatile extern bool Sensor_skewCenter;

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

#endif