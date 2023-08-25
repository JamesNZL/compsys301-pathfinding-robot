/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"

CY_ISR(light_sensed)
{
	Timer_checklight_Start();
    Sensor_Output_1_Write(1);
	isr_lightsense_Disable();
}

CY_ISR(check_light)
{
	if (!Lightsense_Read())
	{
        Sensor_Output_1_Write(0);
        Timer_checklight_Stop();
        isr_lightsense_Enable();
	}
    Timer_checklight_ReadStatusRegister();
}

int main(void)
{
	CyGlobalIntEnable; /* Enable global interrupts. */
	isr_lightsense_StartEx(light_sensed);
	isr_checklight_StartEx(check_light);

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */

	for (;;)
	{
		/* Place your application code here. */
	}
}

/* [] END OF FILE */
