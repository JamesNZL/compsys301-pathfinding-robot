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
void set_pwm_duty_cycle(uint8_t percentage);
//* ========================================
// ADC USART
volatile uint16_t readingIndex = 0;
volatile float results[40];
volatile int16_t counts[40];
volatile uint8_t currentDuty = 100;

CY_ISR(conversion_finished){
    uint16_t result = ADC_GetResult16(0);
    float voltage = ADC_CountsTo_Volts(result);
    uint8_t dac = (voltage/4.08)*(float)255;
    VDAC8_1_SetValue(dac);
    
    /*
    results[readingIndex] = voltage;
    readingIndex++;
    
    if (readingIndex == 40) {
        Timer_TS_Stop();
    }
    */
}

CY_ISR(take_count){
    int16_t count = QuadDec_M1_GetCounter();

    float speed = (float) count/2;
    counts[readingIndex] = speed;
    readingIndex++;
    QuadDec_M1_SetCounter(0);
    if(currentDuty == 100) currentDuty = 0;
    set_pwm_duty_cycle(currentDuty);
    currentDuty += 10;
    if (readingIndex == 11) {
        Timer_1_Stop();
    }
    
}



int main()
{
// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    PWM_1_Start();
    set_pwm_duty_cycle(0);
    QuadDec_M1_Start();
    QuadDec_M1_SetCounter(0);
    Timer_TS_Start();
    Timer_1_Start();
    ADC_Start();
    VDAC8_1_Start();
    isr_calculate_StartEx(take_count);
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
        
        if (readingIndex == 11){
            for(uint16_t i = 0; i < 11; ++i){
                char temp[BUF_SIZE];
                int16_t out = counts[i];
                sprintf(temp, "%i,", out);
                usbPutString(temp);
            }
            readingIndex = 0;
            QuadDec_M1_SetCounter(0);
            Timer_1_Start();
        }
    }   
}

void set_pwm_duty_cycle(uint8_t percentage) {
    // get max count assuming it is 8 bits
    uint8 maxCount = PWM_1_ReadPeriod();
    // set the compare 
    uint8 compare = maxCount - (float)maxCount*((float)percentage/100);
    PWM_1_WriteCompare(compare);
}

void handle_pwm_command(){
    // Valid command
    char percentageString[3]; 
    char message[BUF_SIZE];
    if(entry[0] == 'p' && entry[1] == ' ' && entry[2] != NULL){
        
        usbPutString("p command entered\n");
        //store percentage in a string
        percentageString[0] = entry[2];
        percentageString[1] = entry[3];
        percentageString[2] = entry[4];
        // get integer representation of percentage
        uint8 percentage = atoi(percentageString);
        
        // write appropriate duty cycle
        set_pwm_duty_cycle(percentage);
        
        // display a status message to the terminal
        sprintf(message, "Set the duty cycle to %s\n", percentageString);
        usbPutString(message);
    } else {
        usbPutString("invalid command\n");
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
