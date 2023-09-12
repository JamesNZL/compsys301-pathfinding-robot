#include "commands.h"
#include "common.h"
#include "handlers.h"
#include "movement.h"
#include "usb.h"

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8 FLAGS = 0x00;

int main()
{
	CYGlobalIntEnable;
	PWM_1_Start();
	PWM_2_Start();

	CyDelay(2000);

	Movement_init_decoder_ISR();
	// Movement_turn_right(90);
	// CyDelay(500);
	// Movement_move_mm(500);
	// Movement_set_M1_ctrltarget(300);
	// Movement_set_M2_ctrltarget(300);

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	RF_BT_SELECT_Write(0);

	for (;;)
	{
		/* Place your application code here. */

		//--------------------------------------------

		if (MOVEMENT_PULSES_TO_MOVE <= 0)
		{
			// USB_put_string("STOP!");
			Movement_set_M1_pulse(MOVEMENT_MOTOR_OFF);
			Movement_set_M2_pulse(MOVEMENT_MOTOR_OFF);
		}
		else if (MOVEMENT_PULSES_TO_MOVE < 150)
		{
			// USB_put_string("BRAKE");
			Movement_set_M1_ctrltarget(MOVEMENT_BRAKE_SPEED);
			Movement_set_M2_ctrltarget(MOVEMENT_BRAKE_SPEED);
		}

		if (FLAG_IS_SET(FLAGS, FLAG_ENCODERS_READY))
		{
			// If pulses to move are positive, turn the motors on and subtract from pulses to move.
			if (MOVEMENT_PULSES_TO_MOVE > 0)
			{
				MOVEMENT_PULSES_TO_MOVE -= (MOVEMENT_APPARENT_PULSE_1 > 0) ? MOVEMENT_APPARENT_PULSE_1 : -MOVEMENT_APPARENT_PULSE_1;
			}

			int8 pulseError1 = MOVEMENT_TPULSE_1 / 100 - MOVEMENT_APPARENT_PULSE_1;
			// int8 pulseError2 = MOVEMENT_TPULSE_2 / 100 - MOVEMENT_APPARENT_PULSE_2;
			int8 pulseError2 = MOVEMENT_APPARENT_PULSE_1 - MOVEMENT_APPARENT_PULSE_2;

			// static char entryy[256];
			// sprintf(entryy, "ERR: %d\n;\tTGT2: %d\n;\tM1ENC: %d, M2ENC %d\n\n", pulseError2, MOVEMENT_TPULSE_2, MOVEMENT_APPARENT_PULSE_1, MOVEMENT_APPARENT_PULSE_2);
			// USB_put_string(entryy);

			Movement_set_M1_pulse(MOVEMENT_TPULSE_1 + pulseError1);
			Movement_set_M2_pulse(MOVEMENT_TPULSE_2 + pulseError2 * Kp);

			FLAGS &= ~(1 << FLAG_ENCODERS_READY);
		}

		//--------------------------------------------

		// USB_get_input();

		// if (FLAG_IS_SET(FLAGS, FLAG_USB_INPUT))
		// {
		// 	FLAGS &= ~(1 << FLAG_USB_INPUT);

		// 	char *token = strtok(USB_input, COMMAND_DELIMITER);
		// 	if (token != NULL)
		// 	{
		// 		switch (Commands_match_command(token))
		// 		{
		// 		case (COMMAND_CHANGE_DIRECTION):
		// 		{
		// 			USB_put_string("Parsed command: CHANGE_DIRECTION\n");

		// 			// extract first argument
		// 			token = strtok(NULL, COMMAND_DELIMITER);
		// 			Handlers_change_direction(token);
		// 			break;
		// 		}
		// 		case (COMMAND_CHANGE_DUTY):
		// 		{
		// 			USB_put_string("Parsed command: CHANGE_DUTY\n");

		// 			// extract first argument
		// 			token = strtok(NULL, COMMAND_DELIMITER);
		// 			break;
		// 		}
		// 		case (COMMAND_CHANGE_SPEED):
		// 		{
		// 			USB_put_string("Parsed command: CHANGE_DUTY\n");
		// 			// extract first argument
		// 			token = strtok(NULL, COMMAND_DELIMITER);
		// 			Handlers_change_speed(token);
		// 			break;
		// 		}
		// 		default:
		// 		{
		// 			USB_put_string("Failed to parse command.\n");
		// 			USB_put_string("You Sent:\n");
		// 			USB_put_string(token);
		// 			USB_put_string("\n");
		// 			break;
		// 		}
		// 		}
		// }
		// }
	}
}