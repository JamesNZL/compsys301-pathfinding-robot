#include "battery.h"

#include "common.h"
#include <project.h>

void Battery_display_level(void)
{
	ADC_Battery_Start();
	ADC_Battery_StartConvert();

	while (!ADC_Battery_IsEndConversion(ADC_Battery_RETURN_STATUS))
	{
		;
	}

	// 10k 2.7k resistive divider
	uint16 batteryReading = (ADC_Battery_CountsTo_Volts(ADC_Battery_GetResult16()) * 4704);

	ADC_Battery_Stop();

	// Check if empty
	if (batteryReading <= BATTERY_EMPTY_MV)
	{
		for (uint8 i = 0; i < 255; i++)
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

		return;
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
}