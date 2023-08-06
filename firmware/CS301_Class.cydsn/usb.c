#include "usb.h"
#include "common.h"

#include <project.h>

void USB_put_string(char *s)
{
#ifdef USE_USB
	while (USBUART_CDCIsReady() == 0)
		;

	// ! Assumes that *s is a string with allocated space >= 64 chars
	// ? Since USB implementation restricts data packets to 64 chars, this function truncates the length to 62 chars (63rd char is a '!')
	s[63] = '\0';
	s[62] = '!';

	USBUART_PutData((uint8 *)s, strlen(s));
#endif
}

void USB_put_char(char c)
{
#ifdef USE_USB
	while (USBUART_CDCIsReady() == 0)
		;

	USBUART_PutChar(c);
#endif
}

void USB_get_input(void)
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
