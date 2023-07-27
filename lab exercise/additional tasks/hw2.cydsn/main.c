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

#define CR1_M1_DIRECTION 0
#define CR1_M1_D1 1
#define CR1_M1_D2 2

int main(void)
{
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	PWM_1_Start();
	PWM_1_WriteCompare(PWM_MAX * (float)0.8);

	Control_Reg_1_Write(Control_Reg_1_Read() | (1 << CR1_M1_DIRECTION));

	for (;;)
	{
		/* Place your application code here. */
	}
}

/* [] END OF FILE */
