/* ========================================
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
#include <stdio.h>

#include "defines.h"
#include "vars.h"

void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();

volatile static int8_t convertedValue;
volatile static uint8_t outputValue;
volatile static uint8_t bufferHead = 0;
volatile static uint8_t bufferTail = 0;
CY_ISR(eoc_interrupt)
{
	convertedValue = ADC_SAR_1_GetResult8();
	outputValue = (uint8_t)convertedValue / 2;

	VDAC8_1_SetValue(outputValue);

	usbBuffer[bufferHead++] = outputValue;
	if (bufferHead == BUF_SIZE)
	{
		Timer_1_Stop();
		bufferHead = 0;
	}
}

int main()
{
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	Timer_1_Start();
	ADC_SAR_1_Start();
	VDAC8_1_Start();
	isr_eoc_StartEx(eoc_interrupt);

#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	usbPutString(displaystring);
	for (;;)
	{
		/* Place your application code here. */
		handle_usb();
		if (flag_KB_string == 1)
		{
			usbPutString(line);
			// To avoid duplicate transmissions
			if (strlen(line) > 0)
			{
				usbPutString("\n");
			}
		}

		if (bufferHead != bufferTail)
		{
			sprintf(line, "%d\n", usbBuffer[bufferTail++]);
			usbPutString(line);

			if (bufferTail == BUF_SIZE)
			{
				bufferTail = 0;
			}
		}
		else
		{
			Timer_1_Start();
		}

		flag_KB_string = 0;
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
