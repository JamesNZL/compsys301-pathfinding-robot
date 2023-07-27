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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//* ========================================
#include "commands.h"
#include "defines.h"
#include "vars.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================

static volatile int16_t SPEED_MEASUREMENTS[2];
static volatile uint8_t SPEED_INDEX = 0;
static volatile bool SPEED_FULL = false;
static volatile bool SPEED_CHANGING = false;
CY_ISR(CalculateSpeed)
{
	// skip a timer iteration if the speed was just changed
	if (SPEED_CHANGING)
	{
		SPEED_CHANGING = false;
		return;
	}

	SPEED_MEASUREMENTS[SPEED_INDEX++] = QuadDec_M1_GetCounter();
	if (SPEED_INDEX == 2)
	{
		SPEED_FULL = true;
		SPEED_INDEX = 0;
	}
}

int main(void)
{
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	PWM_1_Start();
	PWM_1_WriteCompare(PWM_MAX * (float)0.8);
	Timer_1_Start();
	QuadDec_M1_Start();
	isr_speed_StartEx(CalculateSpeed);

#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif
	usbPutString(displaystring);
	for (;;)
	{
		/* Place your application code here. */
		static char speedBuffer[20];
		static float dutyCycle = 0.0;
		if (SPEED_FULL == true)
		{
			int16_t speedCSec = SPEED_MEASUREMENTS[1] - (int16_t)SPEED_MEASUREMENTS[0];

			sprintf(speedBuffer, "%d\% => %d\n", dutyCycle * 100, speedCSec);
			usbPutString(speedBuffer);
			SPEED_FULL = false;
			QuadDec_M1_SetCounter(0);

			PWM_1_WriteCompare(PWM_MAX * dutyCycle);
			SPEED_CHANGING = true;
			dutyCycle += 0.1;
			if (dutyCycle == 1.1)
			{
				dutyCycle = 0.0;
			}
		}

		handle_usb();
		if (flag_KB_string == 1)
		{
			usbPutString(line);
			// To avoid duplicate transmissions
			if (strlen(line) > 0)
			{
				usbPutString("\n");
			}

			char *token = strtok(line, COMMAND_DELIMITER);
			if (token != NULL)
			{
				switch (matchCommand(token))
				{
				case (COMMAND_CHANGE_DIRECTION):
				{
					usbPutString("Parsed command: CHANGE_DIRECTION\n");

					Control_Reg_1_Write(Control_Reg_1_Read() ^ (1 << CR1_M1_DIRECTION));

					break;
				}
				case (COMMAND_CHANGE_DUTY):
				{
					usbPutString("Parsed command: CHANGE_DUTY\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					if (strlen(token) == 0)
					{
						break;
					}

					uint8 duty = atoi(token);
					if (duty < 0 || duty > 100)
					{
						usbPutString("Unable to change duty to ");
						usbPutString(token);
						usbPutString("%, must be between 0-100 (inclusive)\n");
						break;
					}

					usbPutString("Changing duty to ");
					usbPutString(token);
					usbPutString("%\n");
					PWM_1_WriteCompare(PWM_MAX * (duty / (float)100));
					break;
				}
				default:
				{
					usbPutString("Failed to parse command.\n");
					break;
				}
				}
			}

			flag_KB_string = 0;
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
