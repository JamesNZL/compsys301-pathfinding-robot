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
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//* ========================================
#include "commands.h"
#include "defines.h"
#include "handlers.h"
#include "movement.h"
#include "vars.h"

// *=======================================
void handle_usb();
void usb_put_string(char *s);
void usb_put_char(char c);

int main()
{
	// --------------------------------
	// ----- INITIALIZATIONS ----------
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();
// ------USB SETUP ----------------
#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	RF_BT_SELECT_Write(0);

	for (;;)
	{
		/* Place your application code here. */
		handle_usb();
		if (flag_KB_string == 1)
		{
			char *token = strtok(line, COMMAND_DELIMITER);
			if (token != NULL)
			{
				switch (Commands_match_command(token))
				{
				case (COMMAND_CHANGE_DIRECTION):
				{
					usb_put_string("Parsed command: CHANGE_DIRECTION\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_direction(token);
					break;
				}
				case (COMMAND_CHANGE_DUTY):
				{
					usb_put_string("Parsed command: CHANGE_DUTY\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					break;
				}
				case (COMMAND_CHANGE_SPEED):
				{
					usb_put_string("Parsed command: CHANGE_DUTY\n");
					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_speed(token);
					break;
				}
				default:
				{
					usb_put_string("Failed to parse command.\n");
					usb_put_string("You Sent:\n");
					usb_put_string(token);
					usb_put_string("\n");
					break;
				}
				}
			}
			flag_KB_string = 0;
		}
	}
}
//* ========================================
void usb_put_string(char *s)
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
void usb_put_char(char c)
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
