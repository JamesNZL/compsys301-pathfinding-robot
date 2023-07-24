/* ========================================
 * Fully working code: 
 * PWM      : 
 * Encoder  : 
 * ADC      :
 * USB      : port displays speed and position.
 * CMD: "PW xx"
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
//* ========================================
#include "defines.h"
#include "vars.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
void handle_pwm_command();
//* ========================================
volatile uint8_t readingIndex = 0;
volatile uint16_t buffer[40];

CY_ISR(conversion_finished){
    uint16_t result = ADC_GetResult16(0);
    float voltage = (2.048*(float)result)/1023;
    uint8_t dac = (voltage/4.08)*256;
    VDAC8_1_SetValue(dac);
    buffer[readingIndex] = result;
    readingIndex++;
    if (readingIndex == 40) {
        Timer_TS_Stop();
    }
}



int main()
{
// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    PWM_1_Start();
    Timer_TS_Start();
    ADC_Start();
    VDAC8_1_Start();
    isr_eoc_StartEx(conversion_finished);
// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);
    
    usbPutString(displaystring);
    for(;;)
    {
        /* Place your application code here. */
        handle_usb();
        if (flag_KB_string == 1)
        {
            handle_pwm_command();
            flag_KB_string = 0;
        }
        
        if (readingIndex == 40) {
            readingIndex = 0;
            char temp[BUF_SIZE];
            for(uint8_t i = 0; i < 40; ++i){
                sprintf(temp, "%i,", buffer[i]);
                usbPutString(temp);
            }
        }
    }   
}

void handle_pwm_command(){
    // Valid command
    char percentageString[3]; 
    char message[BUF_SIZE];
    if(entry[0] == 'p' && entry[1] == ' ' && entry[2] != NULL){
        
        usbPutString("p command entered");
        //store percentage in a string
        percentageString[0] = entry[2];
        percentageString[1] = entry[3];
        percentageString[2] = entry[4];
        // get integer representation of percentage
        uint8 percentage = atoi(percentageString);
        // get max count assuming it is 8 bits
        uint8 maxCount = PWM_1_ReadPeriod();
        
        // set the compare 
        uint8 compare = maxCount - (float)maxCount*((float)percentage/100);
        PWM_1_WriteCompare(compare);
        
        // display a status message to the terminal
        sprintf(message, "Set the duty cycle to %s", percentageString);
        usbPutString(message);
    } else {
        usbPutString("invalid command");
    }
}

//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
//* ========================================
void handle_usb()
{
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'line' and 'flag_KB_string' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;
    uint8 c; 
    

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
        if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();

            if ((c == 13) || (c == 10))
            {
//                if (usbBufCount > 0)
                {
                    entry[usbBufCount]= '\0';
                    strcpy(line,entry);
                    usbBufCount = 0;
                    flag_KB_string = 1;
                }
            }
            else 
            {
                if (((c == CHAR_BACKSP) || (c == CHAR_DEL) ) && (usbBufCount > 0) )
                    usbBufCount--;
                else
                {
                    if (usbBufCount > (BUF_SIZE-2) ) // one less else strtok triggers a crash
                    {
                       USBUART_PutChar('!');        
                    }
                    else
                        entry[usbBufCount++] = c;  
                }  
            }
        }
    }    
}


/* [] END OF FILE */
