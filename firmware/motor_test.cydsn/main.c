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
#include "defines.h"
#include "project.h"
#include "vars.h"

#include <stdio.h>

void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();

static volatile int16_t SPEED_MEASUREMENTS_M1[2];
static volatile int16_t SPEED_MEASUREMENTS_M2[2];
static volatile uint8_t SPEED_INDEX = 0;
static volatile uint8_t SPEED_FULL = FALSE;
static volatile uint8_t SPEED_CHANGING = FALSE;
CY_ISR(CalculateSpeed)
{
	// skip a timer iteration if the speed was just changed
	if (SPEED_CHANGING)
	{
		SPEED_CHANGING = FALSE;
		SPEED_FULL = FALSE;
		SPEED_INDEX = 0;
	}
	else
	{
		SPEED_MEASUREMENTS_M1[SPEED_INDEX] = QuadDec_M1_GetCounter();
		SPEED_MEASUREMENTS_M2[SPEED_INDEX] = QuadDec_M2_GetCounter();
		SPEED_INDEX++;
		if (SPEED_INDEX == 2)
		{
			SPEED_FULL = TRUE;
			SPEED_INDEX = 0;
		}
	}
}

uint8 battery_reading;
char bat_entry[20];

CY_ISR(SenseBattery)
{
    battery_reading = (ADC_SAR_1_CountsTo_Volts(ADC_SAR_1_GetResult16()) * 3.518);
}

int main(void)
{
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	PWM_M1_Start();
	PWM_M2_Start();
	Timer_Speed_Start();
	QuadDec_M1_Start();
	QuadDec_M2_Start();
	isr_speed_StartEx(CalculateSpeed);
    ADC_SAR_1_Start();
	isr_bat_StartEx(SenseBattery);

	PWM_M1_WriteCompare(0);
	PWM_M2_WriteCompare(0);

#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif
	for (;;)
	{
		/* Place your application code here. */
		static uint8_t dutyCycle = 0;
		if (SPEED_FULL == TRUE)
		{
			SPEED_FULL = FALSE;
			QuadDec_M1_SetCounter(0);
			QuadDec_M2_SetCounter(0);

			int16_t speedCSecM1 = SPEED_MEASUREMENTS_M1[1] - SPEED_MEASUREMENTS_M1[0];
			int16_t speedCSecM2 = SPEED_MEASUREMENTS_M2[1] - SPEED_MEASUREMENTS_M2[0];

			sprintf(line, "M1: %d%% => %d\n", dutyCycle, speedCSecM1);
			usbPutString(line);

			sprintf(line, "M2: %d%% => %d\n", dutyCycle, speedCSecM2);
			usbPutString(line);

			SPEED_CHANGING = TRUE;
			dutyCycle += 10;
			if (dutyCycle > 100)
			{
				dutyCycle = 0;
			}

			PWM_M1_WriteCompare(PWM_MAX * (dutyCycle / (float)100));
			PWM_M2_WriteCompare(PWM_MAX * (dutyCycle / (float)100));
            
            sprintf(bat_entry, "%d\n", battery_reading);
            usbPutString(bat_entry);
		}
	}
}
//* ========================================
void usbPutString(char *s)
{
	// !! Assumes that *s is a string with allocated space >=64 chars
	//  Since USB implementation retricts data packets to 64 chars, this function truncates the
	//  length to 62 char (63rd char is a '!')

#ifdef USE_USB
	while (USBUART_CDCIsReady() == 0)
		;
	s[63] = '\0';
	s[62] = '!';
	USBUART_PutData((uint8 *)s, strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB
	while (USBUART_CDCIsReady() == 0)
		;
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
					entry[usbBufCount] = '\0';
					strcpy(line, entry);
					usbBufCount = 0;
					flag_KB_string = 1;
				}
			}
			else
			{
				if (((c == CHAR_BACKSP) || (c == CHAR_DEL)) && (usbBufCount > 0))
					usbBufCount--;
				else
				{
					if (usbBufCount > (BUF_SIZE - 2)) // one less else strtok triggers a crash
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
