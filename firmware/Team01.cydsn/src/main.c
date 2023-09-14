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
	Movement_move_mm(2000);
	// Movement_set_M1_ctrlconst(MOVEMENT_RUN_SPEED);
	// Movement_set_M2_ctrlconst(MOVEMENT_RUN_SPEED);

#ifdef USB_ENABLED
	USBUART_Start(0, USBUART_5V_OPERATION);
#endif

	RF_BT_SELECT_Write(0);

	for (;;)
	{
		/* Place your application code here. */

		//--------------------------------------------

		Movement_check_dist();
		Movement_next_control_cycle();

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