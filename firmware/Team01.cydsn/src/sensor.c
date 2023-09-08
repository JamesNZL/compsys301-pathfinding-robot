#include "sensor.h"
#include "common.h"
#include <project.h>

void Sensor_init_sensors()
{
	isr_lightsense_StartEx(light_sensed);
	isr_lightcheck_StartEx(check_light);
}