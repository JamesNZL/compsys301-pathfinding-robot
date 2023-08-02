
/* ========================================
 * Laboratory Exercise 3
 *
 * Program timer to flash LED at 1Hz, use interrupts
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <project.h>

CY_ISR(timerInterrupt);

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timer_1_Start();
    isr_TC_StartEx(timerInterrupt);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */

        
    }
}

CY_ISR(timerInterrupt){
    LED_Write(!LED_Read());
    Timer_1_ReadStatusRegister();
}



/* [] END OF FILE */
