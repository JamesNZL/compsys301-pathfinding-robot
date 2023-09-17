#include "battery.h"

#include "common.h"
#include <project.h>

uint16 Battery_display_level(void)
{
	ADC_Battery_Start();

	// Wait for the voltage level to settle
	// ! This is very important as there is >5ms charging time on the V_Battery pin!
	CyDelay(15);

	uint16 sum = 0;
	for (uint8 i = 0; i < BATTERY_SAMPLES_COUNT; i++)
	{
		ADC_Battery_StartConvert();

		while (!ADC_Battery_IsEndConversion(ADC_Battery_RETURN_STATUS))
		{
			;
		}

		sum += ADC_Battery_CountsTo_mVolts(ADC_Battery_GetResult16());
	}

	uint16 batteryReading = (sum / BATTERY_SAMPLES_COUNT) * BATTERY_DIVIDER_GAIN;

	ADC_Battery_Stop();

	// Check if empty
	if (batteryReading <= BATTERY_EMPTY_MV)
	{
		for (uint8 i = 0; i < BATTERY_LOW_FLASH_COUNT; i++)
		{
			DB0_TOGGLE_LED;
			DB1_TOGGLE_LED;
			DB2_TOGGLE_LED;
			DB3_TOGGLE_LED;
			DB4_TOGGLE_LED;
			DB5_TOGGLE_LED;
			DB6_TOGGLE_LED;
			DB7_TOGGLE_LED;

			CyDelay(150);
		}

		return batteryReading;
	}

	uint8 batteryPercentage = ((batteryReading - BATTERY_EMPTY_MV) * 100) / (BATTERY_FULL_MV - BATTERY_EMPTY_MV);

	// First turn all LEDs on
	DB0_ON;
	DB1_ON;
	DB2_ON;
	DB3_ON;
	DB4_ON;
	DB5_ON;
	DB6_ON;
	DB7_ON;

	// Turn LEDs off as required
	if (batteryPercentage < 88)
	{
		DB0_OFF;
	}
	if (batteryPercentage < 75)
	{
		DB1_OFF;
	}
	if (batteryPercentage < 63)
	{
		DB2_OFF;
	}
	if (batteryPercentage < 50)
	{
		DB3_OFF;
	}
	if (batteryPercentage < 38)
	{
		DB4_OFF;
	}
	if (batteryPercentage < 25)
	{
		DB5_OFF;
	}
	if (batteryPercentage < 13)
	{
		DB6_OFF;
	}

	return batteryReading;
}