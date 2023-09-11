#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE		0
#define SENSOR_COUNT				7
#define SENSOR_TURN_SENSOR_POS_1	0
#define SENSOR_TURN_SENSOR_POS_2	0
#define SENSOR_SKEW_SENSOR_1		0
#define SENSOR_DEFAULT_BIAS_VOLTAGE 1.5F

void Sensor_init_sensors();

void Sensor_set_bias_level(float voltage);

#endif