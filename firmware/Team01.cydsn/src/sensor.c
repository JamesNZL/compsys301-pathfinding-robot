#include "sensor.h"
#include "common.h"
#include <project.h>

CY_ISR(light_sensed)
{
	Timer_Light_Check_Start();
	isr_lightsense_Disable();
}

CY_ISR(check_light)
{
	// sensors.sensor1 = Is_White1_Read()
	// sensors.sensor2 = Is_White2_Read()
	// ...

	if (!(Is_White1_Read() || Is_White2_Read() || Is_White3_Read() || Is_White4_Read() || Is_White5_Read() || Is_White6_Read() || Is_White7_Read())) // sensor1 or sensor2 or sensor3 ...
	{
		// Safeguard
		Timer_Light_Check_Stop();
		isr_lightsense_Enable();
	}
	Timer_Light_Check_ReadStatusRegister();
}

void Sensor_init_sensors()
{
	DAC_Lower_Start();
	DAC_Upper_Start();
	Sensor_set_bias_level(SENSOR_DEFAULT_BIAS_VOLTAGE);
	isr_lightsense_StartEx(light_sensed);
	isr_lightcheck_StartEx(check_light);
}

void Sensor_set_bias_level(float voltage)
{

	uint8_t dacValue = (voltage / DAC_Lower_RANGE_4V) * 255;

	DAC_Lower_SetValue(dacValue);
	DAC_Upper_SetValue(dacValue);
}