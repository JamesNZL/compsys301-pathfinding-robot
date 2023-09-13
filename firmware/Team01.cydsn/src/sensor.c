#include "sensor.h"

volatile Sensor Sensor_turnLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_turnRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewBackRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewBackLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewFrontRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewFrontLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewCenter = SENSOR_DEFAULT_INITIALISATION;

volatile uint8 Sensor_sampledPeriods = 0;

CY_ISR(light_sensed)
{
	isr_lightsense_Disable();
	Timer_Light_Check_Start();
}

CY_ISR(check_light)
{
	Sensor_sampledPeriods++;
	Sensor_sample_sensor_readings();
	if (Sensor_sampledPeriods >= SENSOR_SAMPLING_PERIODS) // sensor1 or sensor2 or sensor3 ...
	{
		Sensor_store_sensor_statuses();
		// Safeguard
		Sensor_sampledPeriods = 0;
		Timer_Light_Check_Stop();
		isr_lightsense_Enable();
	}
}

bool Sensor_all_sensors_off()
{
	return !(Sensor_turnLeft.status || Sensor_turnRight.status
		|| Sensor_skewBackRight.status || Sensor_skewBackLeft.status || Sensor_skewCenter.status
		|| Sensor_skewFrontLeft.status || Sensor_skewFrontRight.status);
}

bool Sensor_on_right_turn_intersection()
{
	return !Sensor_turnLeft.status && Sensor_turnRight.status;
}

bool Sensor_on_left_turn_intersection()
{
	return Sensor_turnLeft.status && !Sensor_turnRight.status;
}

bool Sensor_on_all_turn_intersection()
{
	return Sensor_turnLeft.status && Sensor_turnRight.status;
}

void Sensor_store_sensor_statuses()
{

	SENSOR_UPDATE_STATUS(Sensor_turnLeft);
	SENSOR_UPDATE_STATUS(Sensor_turnRight);
	SENSOR_UPDATE_STATUS(Sensor_skewBackRight);
	SENSOR_UPDATE_STATUS(Sensor_skewBackLeft);
	SENSOR_UPDATE_STATUS(Sensor_skewFrontRight);
	SENSOR_UPDATE_STATUS(Sensor_skewFrontLeft);
	SENSOR_UPDATE_STATUS(Sensor_skewCenter);
}

void Sensor_sample_sensor_readings()
{
	SENSOR_PROCESS_READING(Sensor_turnLeft, Turn_Left_Read);
	SENSOR_PROCESS_READING(Sensor_turnRight, Turn_Right_Read);
	SENSOR_PROCESS_READING(Sensor_skewBackRight, Skew_Back_Right_Read);
	SENSOR_PROCESS_READING(Sensor_skewBackLeft, Skew_Back_Left_Read);
	SENSOR_PROCESS_READING(Sensor_skewFrontRight, Skew_Front_Right_Read);
	SENSOR_PROCESS_READING(Sensor_skewFrontLeft, Skew_Front_Left_Read);
	SENSOR_PROCESS_READING(Sensor_skewCenter, Skew_Center_Read);
}
void Sensor_write_statuses_to_debug()
{

	DB0_Write(Sensor_turnLeft.status);
	DB1_Write(Sensor_turnRight.status);
	DB2_Write(Sensor_skewBackRight.status);
	DB3_Write(Sensor_skewBackLeft.status);
	DB4_Write(Sensor_skewFrontRight.status);
	DB5_Write(Sensor_skewFrontLeft.status);
	DB6_Write(Sensor_skewCenter.status);
}

void Sensor_init_sensors()
{
	DAC_Lower_Start();
	DAC_Upper_Start();
	DAC_Middle_Start();
	Sensor_set_bias_level(SENSOR_DEFAULT_BIAS_VOLTAGE);
	isr_lightsense_StartEx(light_sensed);
	isr_lightcheck_StartEx(check_light);
}

void Sensor_set_bias_level(float voltage)
{
	uint8_t dacValue = (voltage / DAC_Lower_RANGE_4V) * 255;

	DAC_Lower_SetValue(dacValue);
	DAC_Middle_SetValue(dacValue);
	DAC_Upper_SetValue(dacValue);
}