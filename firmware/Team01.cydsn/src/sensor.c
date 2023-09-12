#include "sensor.h"

volatile bool Sensor_turnLeft = FALSE;
volatile bool Sensor_turnRight = FALSE;
volatile bool Sensor_skewBackRight = FALSE;
volatile bool Sensor_skewBackLeft = FALSE;
volatile bool Sensor_skewFrontRight = FALSE;
volatile bool Sensor_skewFrontLeft = FALSE;
volatile bool Sensor_skewCenter = FALSE;

CY_ISR(light_sensed)
{
	Timer_Light_Check_Start();
	isr_lightsense_Disable();
}

CY_ISR(check_light)
{
	Sensor_store_sensor_statuses();

	bool allLightsOff = !(Sensor_turnLeft || Sensor_turnRight
		|| Sensor_skewBackRight || Sensor_skewBackLeft || Sensor_skewCenter
		|| Sensor_skewFrontLeft || Sensor_skewFrontRight);

	if (allLightsOff) // sensor1 or sensor2 or sensor3 ...
	{
		// Safeguard
		Timer_Light_Check_Stop();
		isr_lightsense_Enable();
	}
	Timer_Light_Check_ReadStatusRegister();
}

void Sensor_store_sensor_statuses()
{
	Sensor_turnLeft = Turn_Left_Read();
	Sensor_turnRight = Turn_Right_Read();
	Sensor_skewBackRight = Skew_Back_Right_Read();
	Sensor_skewBackLeft = Skew_Back_Left_Read();
	Sensor_skewFrontRight = Skew_Front_Right_Read();
	Sensor_skewFrontLeft = Skew_Front_Left_Read();
	Sensor_skewCenter = Skew_Center_Read();
}

void Sensor_write_statuses_to_debug()
{
	DB0_Write(Sensor_turnLeft);
	DB1_Write(Sensor_turnRight);
	DB2_Write(Sensor_skewBackRight);
	DB3_Write(Sensor_skewBackLeft);
	DB4_Write(Sensor_skewFrontRight);
	DB5_Write(Sensor_skewFrontLeft);
	DB6_Write(Sensor_skewCenter);
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