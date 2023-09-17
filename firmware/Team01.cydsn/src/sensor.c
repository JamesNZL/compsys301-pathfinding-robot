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
	Sensor_prepare_for_sampling();
}

CY_ISR(check_light)
{
	// If we have exceeded the maximum time without a rising edge
	if (FLAG_IS_SET(FLAGS, FLAG_SENSOR_AWAIT_RISING))
	{
		Sensor_handle_missing_rising_edge();
		return;
	}

	// SAMPLING
	Sensor_sample_sensor_readings();
	Sensor_sampledPeriods++;

	// We have taken all samples needed for this rising edge
	if (Sensor_sampledPeriods >= SENSOR_SAMPLING_PERIODS)
	{
		Sensor_prepare_for_next_rising_edge();
		return;
	}
}

bool Sensor_is_all_sensors_off()
{
	return !(
		Sensor_turnLeft.status
		|| Sensor_turnRight.status
		|| Sensor_skewBackRight.status
		|| Sensor_skewBackLeft.status
		|| Sensor_skewCenter.status
		|| Sensor_skewFrontLeft.status
		|| Sensor_skewFrontRight.status);
}

bool Sensor_is_on_right_turn_intersection()
{
	return Sensor_turnLeft.status && !Sensor_turnRight.status;
}

bool Sensor_is_on_left_turn_intersection()
{
	return !Sensor_turnLeft.status && Sensor_turnRight.status;
}

bool Sensor_is_on_all_turn_intersection()
{
	return !Sensor_turnLeft.status && !Sensor_turnRight.status;
}

SensorActions Sensor_determine_action()
{
#ifndef SENSOR_USE_LOOKUP
	/*
	if ((!Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (!Sensor_skewCenter.status && Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && Sensor_turnLeft.status && Sensor_turnRight.status)
			|| (Sensor_skewCenter.status && Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && Sensor_turnLeft.status && Sensor_turnRight.status)
			|| (!Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status))
		{
			return SENSOR_ACTION_CONTINUE_FORWARD;
		}

		if ((Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && Sensor_skewBackRight.status))
		{
			return SENSOR_ACTION_CONTINUE_PREVIOUS;
		}

		if ((!Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (!Sensor_skewFrontLeft.status && !Sensor_skewBackLeft.status && Sensor_skewBackRight.status)
			|| (!Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status)
			|| (!Sensor_skewCenter.status && Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && !Sensor_turnLeft.status)
			|| (Sensor_skewCenter.status && !Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && Sensor_turnLeft.status && !Sensor_turnRight.status))
		{
			return SENSOR_ACTION_CORRECT_LEFT;
		}

		if ((Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (!Sensor_skewCenter.status && Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (!Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (!Sensor_skewCenter.status && Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && !Sensor_turnLeft.status)
			|| (Sensor_skewCenter.status && Sensor_skewFrontLeft.status && !Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status && Sensor_turnLeft.status && !Sensor_turnRight.status))
		{
			return SENSOR_ACTION_CORRECT_RIGHT;
		}

		if ((Sensor_skewCenter.status && Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && !Sensor_skewBackRight.status)
			|| (Sensor_skewCenter.status && Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && !Sensor_skewBackLeft.status))
		{
			return SENSOR_ACTION_DETERMINE_SKEW_OR_TURN_ABOUT;
		}

		if (Sensor_skewFrontLeft.status && Sensor_skewFrontRight.status && Sensor_skewBackLeft.status && Sensor_skewBackRight.status)
		{
			return SENSOR_ACTION_FIND_VALID_STATE;
		}
	 */

	if ((Sensor_skewBackLeft.status && Sensor_skewFrontRight.status) || (Sensor_skewFrontRight.status && Sensor_skewBackRight.status))
	{
		return SENSOR_ACTION_CORRECT_LEFT;
	}
	else if ((Sensor_skewBackRight.status && Sensor_skewFrontLeft.status) || (Sensor_skewFrontLeft.status && Sensor_skewBackLeft.status))
	{
		return SENSOR_ACTION_CORRECT_RIGHT;
	}
	else
	{
		return SENSOR_ACTION_CONTINUE_FORWARD;
	}
#endif

#ifdef SENSOR_USE_LOOKUP
	uint8 bitfield = ((Sensor_skewCenter.status << 6)
		| (Sensor_skewFrontLeft.status << 5)
		| (Sensor_skewFrontRight.status << 4)
		| (Sensor_skewBackLeft.status << 3)
		| (Sensor_skewBackRight.status << 2)
		| (Sensor_turnLeft.status << 1)
		| (Sensor_turnRight.status << 0));

	return SENSOR_ACTION_LUT[bitfield];
#endif
}

void Sensor_set_light_check_timer_period(uint16 period)
{
	Timer_Light_Check_Stop();
	Timer_Light_Check_WritePeriod(period);
	Timer_Light_Check_WriteCounter(period);
	Timer_Light_Check_Start();
}

void Sensor_debounce_and_update_sensor_statuses()
{
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_turnLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_turnRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewBackRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewBackLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewFrontRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewFrontLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewCenter);
}

void Sensor_sample_sensor_readings()
{
	SENSOR_SAMPLE_READING(Sensor_turnLeft, Turn_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_turnRight, Turn_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewBackRight, Skew_Back_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewBackLeft, Skew_Back_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_skewFrontRight, Skew_Front_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewFrontLeft, Skew_Front_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_skewCenter, Skew_Center_Read);
}
void Sensor_write_statuses_to_debug()
{
	DB0_Write(Sensor_skewFrontLeft.status);
	DB1_Write(Sensor_turnLeft.status);
	DB2_Write(Sensor_skewBackLeft.status);
	DB3_Write(Sensor_skewCenter.status);
	DB4_Write(Sensor_skewFrontRight.status);
	DB5_Write(Sensor_turnRight.status);
	DB6_Write(Sensor_skewBackRight.status);
}

void Sensor_init_sensors()
{
	DAC_Lower_Start();
	DAC_Upper_Start();
	DAC_Middle_Start();
	Sensor_set_bias_level(SENSOR_DEFAULT_BIAS_VOLTAGE_VOLTS);
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

void Sensor_write_low_all_sensors()
{
	SENSOR_WRITE_LOW(Sensor_turnLeft);
	SENSOR_WRITE_LOW(Sensor_turnRight);
	SENSOR_WRITE_LOW(Sensor_skewBackLeft);
	SENSOR_WRITE_LOW(Sensor_skewBackRight);
	SENSOR_WRITE_LOW(Sensor_skewFrontLeft);
	SENSOR_WRITE_LOW(Sensor_skewFrontRight);
	SENSOR_WRITE_LOW(Sensor_skewCenter);
}

void Sensor_prepare_for_sampling()
{
	FLAG_CLEAR(FLAGS, FLAG_SENSOR_AWAIT_RISING);
	isr_lightsense_Disable();
	Sensor_set_light_check_timer_period(SENSOR_SAMPLING_TIMER_PERIOD);

#ifdef SENSOR_DISPLAY_ON_DEBUG
	DB7_OFF;
#endif
}

void Sensor_prepare_for_next_rising_edge()
{
	Sensor_debounce_and_update_sensor_statuses();
	Sensor_sampledPeriods = 0;
	FLAG_SET(FLAGS, FLAG_SENSOR_AWAIT_RISING);
	Sensor_set_light_check_timer_period(SENSOR_RISING_EDGE_MAX_DELAY_TIMER_PERIOD);
	isr_lightsense_Enable();
}

void Sensor_handle_missing_rising_edge()
{
	Timer_Light_Check_Stop();
	Sensor_write_low_all_sensors();

#ifdef SENSOR_DISPLAY_ON_DEBUG
	DB7_ON;
#endif
}