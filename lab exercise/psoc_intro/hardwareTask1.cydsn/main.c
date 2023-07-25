
/* ========================================
 * Hardware Exercise 1
 *
 * Send analog measurements to USB
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

CY_ISR(eocInterrupt){
    LED_Write(~LED_Read());
    VDAC8_1_SetValue(ADC_SAR_1_GetResult8()/2);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timer_1_Start();
    ADC_SAR_1_Start();
    VDAC8_1_Start();
    ADC_SAR_1_IRQ_Start();
    isr_EOC_StartEx(eocInterrupt);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    VDAC8_1_SetValue(150);
    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
