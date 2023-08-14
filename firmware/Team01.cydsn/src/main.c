#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "movement.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8_t FLAGS = 0x00;

int main()
{
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();

	init_control_loop();

	set_target_pulse_L(30);
	set_target_pulse_R(50);

#ifdef USE_USB
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	RF_BT_SELECT_Write(0);

	for (;;)
	{
		PULSE_ERROR = TARGET_PULSE_L - APPARENT_PULSE_L;
		correction = PULSE_ERROR / TARGET_PULSE_L * PWM_MAX;
		next_PWM = CURRENT_PWM_L + PULSE_ERROR / 4; //> PWM_MAX ? PWM_MAX : CURRENT_PWM_L + correction;
		PWM_1_WriteCompare(next_PWM);

		PULSE_ERROR = TARGET_PULSE_R - APPARENT_PULSE_R;
		correction = PULSE_ERROR / TARGET_PULSE_R * PWM_MAX;
		next_PWM = CURRENT_PWM_R + correction > PWM_MAX ? PWM_MAX : CURRENT_PWM_R + correction;
		PWM_2_WriteCompare(next_PWM);
		/* Place your application code here. */
		USB_get_input();

		if (IS_SET(FLAGS, FLAG_USB_INPUT))
		{
			FLAGS &= ~(1 << FLAG_USB_INPUT);

			char *token = strtok(USB_input, COMMAND_DELIMITER);
			if (token != NULL)
			{
				switch (Commands_match_command(token))
				{
				case (COMMAND_CHANGE_DIRECTION):
				{
					USB_put_string("Parsed command: CHANGE_DIRECTION\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_direction(token);
					break;
				}
				case (COMMAND_CHANGE_DUTY):
				{
					USB_put_string("Parsed command: CHANGE_DUTY\n");

					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					break;
				}
				case (COMMAND_CHANGE_SPEED):
				{
					USB_put_string("Parsed command: CHANGE_DUTY\n");
					// extract first argument
					token = strtok(NULL, COMMAND_DELIMITER);
					Handlers_change_speed(token);
					break;
				}
				default:
				{
					USB_put_string("Failed to parse command.\n");
					USB_put_string("You Sent:\n");
					USB_put_string(token);
					USB_put_string("\n");
					break;
				}
				}
			}
		}
	}
}