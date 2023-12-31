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
			DEBUG_ALL_TOGGLE;

			CyDelay(150);
		}

		return batteryReading;
	}

	uint8 batteryPercentage = ((batteryReading - BATTERY_EMPTY_MV) * 100) / (BATTERY_FULL_MV - BATTERY_EMPTY_MV);

	DEBUG_7_ON;

	if (batteryPercentage > 13)
	{
		DEBUG_6_ON;
	}
	if (batteryPercentage > 25)
	{
		DEBUG_5_ON;
	}
	if (batteryPercentage > 38)
	{
		DEBUG_4_ON;
	}
	if (batteryPercentage > 50)
	{
		DEBUG_3_ON;
	}
	if (batteryPercentage > 63)
	{
		DEBUG_2_ON;
	}
	if (batteryPercentage > 75)
	{
		DEBUG_1_ON;
	}
	if (batteryPercentage > 88)
	{
		DEBUG_0_ON;
	}

	return batteryReading;
}