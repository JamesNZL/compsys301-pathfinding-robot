
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

CY_ISR(timer_interrupt){
    LED_Write(~LED_Read());
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Timer_1_Start();
    isr_TC_Enable();
    isr_TC_StartEx(timer_interrupt);
    
    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
