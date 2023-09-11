#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE		0
#define SENSOR_COUNT				7
#define SENSOR_DEFAULT_BIAS_VOLTAGE 1.5F

#include "common.h"
#include <project.h>

volatile extern bool Sensor_turnLeft;
volatile extern bool Sensor_turnRight;
volatile extern bool Sensor_skewBackRight;
volatile extern bool Sensor_skewBackLeft;
volatile extern bool Sensor_skewFrontRight;
volatile extern bool Sensor_skewFrontLeft;
volatile extern bool Sensor_skewCenter;

void Sensor_init_sensors();

void Sensor_set_bias_level(float voltage);

#endif