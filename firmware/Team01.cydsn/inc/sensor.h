#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_HARDWARE_MODE	 0;
#define SENSOR_COUNT			 7;
#define SENSOR_TURN_SENSOR_POS_1 0;
#define SENSOR_TURN_SENSOR_POS_2 0;
#define SENSOR_SKEW_SENSOR_1	 0;

CY_ISR(light_sensed)
{
	Timer_Light_Check_Start();
	isr_lightsense_Disable();
}

CY_ISR(check_light)
{
	// sensors.sensor1 = Is_White1_Read()

	if (!(Is_White1_Read() ||))
	{
		Timer_Light_Check_Stop();
		isr_lightsense_Enable();
	}
	Timer_checklight_ReadStatusRegister();
}

void Sensor_init_sensors();

#endif