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

#define PWM_MAX 255 // maximum value of duty cycle
#define PWM_MIN 0 // minimum value of duty cycle

int main(void)
{
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	PWM_1_Start();
	PWM_1_WriteCompare(PWM_MAX * (float)0.8);

	for (;;)
	{
		/* Place your application code here. */
	}
}

/* [] END OF FILE */
