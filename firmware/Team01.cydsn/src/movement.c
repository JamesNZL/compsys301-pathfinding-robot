#include "movement.h"
#include "common.h"
#include <project.h>

const uint8 MOVEMENT_SPEED_BRAKE = 150;
uint16 MOVEMENT_SPEED_RUN = 170;
const uint16 MOVEMENT_SPEED_TURN = 120;

const uint8 MOVEMENT_CORRECTION_SKEW = 20;
const int8 MOVEMENT_CORRECTION_TURNS = -9;

const uint8 MOVEMENT_CONTROLLER_GAIN = 1;

volatile uint32 MOVEMENT_TIME_ELAPSED_AFTER_TURN = 0;

CY_ISR(PROCESS_PULSE)
{
	MOVEMENT_PULSE_APPARENT_1 = QuadDec_M1_GetCounter();
	MOVEMENT_PULSE_APPARENT_2 = QuadDec_M2_GetCounter();

	FLAG_SET(FLAGS, FLAG_ENCODERS_READY);

	QuadDec_M1_SetCounter(0);
	QuadDec_M2_SetCounter(0);
	Timer_Dec_ReadStatusRegister();
}

uint16 Movement_cm_to_pulse(float cm)
{
	return (uint16)(cm * MOVEMENT_CM_CONVERSION);
}

void Movement_check_distance()
{
	if (FLAG_IS_SET(FLAGS, FLAG_MOVE_INFINITELY))
	{
		if (FLAG_IS_SET(FLAGS, FLAG_WAITING_AFTER_TURN))
		{
			MOVEMENT_TIME_ELAPSED_AFTER_TURN++;
			if (MOVEMENT_TIME_ELAPSED_AFTER_TURN >= MOVEMENT_DELAY_AFTER_TURN)
			{
				FLAG_CLEAR(FLAGS, FLAG_WAITING_AFTER_TURN);
				MOVEMENT_TIME_ELAPSED_AFTER_TURN = 0;
			}
		}
		return;
	}

	if (MOVEMENT_PULSES_TO_MOVE <= 0)
	{
		Movement_set_M1_pulse_target(MOVEMENT_MOTOR_OFF);
		Movement_set_M2_pulse_target(MOVEMENT_MOTOR_OFF);
		Motor_Control_Reg_Write(Motor_Control_Reg_Read() | (1 << MOTOR_DISABLE_CR_POS));
	}
	else if (MOVEMENT_PULSES_TO_MOVE < 150)
	{
		Movement_set_M1_pulse_target(MOVEMENT_SPEED_BRAKE);
		Movement_set_M2_pulse_target(MOVEMENT_SPEED_BRAKE);
	}
}

void Movement_next_control_cycle()
{
	if (FLAG_IS_CLEARED(FLAGS, FLAG_ENCODERS_READY))
	{
		return;
	}

	// Subtract read pulses from distance to travel
	if (MOVEMENT_PULSES_TO_MOVE > 0)
	{
		MOVEMENT_PULSES_TO_MOVE -= MOVEMENT_PULSE_APPARENT_1;
	}

	// Samples taken every 25th of a second. Divide target by 25 to get expected 25th of a second pulses
	int8 pulseError1 = (MOVEMENT_PULSE_TARGET_1 / 25) - MOVEMENT_PULSE_APPARENT_1;
	int8 pulseError2 = (MOVEMENT_PULSE_TARGET_2 / 25) - MOVEMENT_PULSE_APPARENT_2;
	// int8 pulseError2 = MOVEMENT_PULSE_APPARENT_1 - MOVEMENT_PULSE_APPARENT_2; // For shimmy shimmy

	uint16 target1 = MOVEMENT_PULSE_VARYING_1 + pulseError1;
	uint16 target2 = MOVEMENT_PULSE_VARYING_2 + pulseError2;

	Movement_write_M1_pulse(target1);
	Movement_write_M2_pulse(target2);

	// Make the varying pulses change up or down accordingly to the observed speed
	Movement_set_M1_pulse_varying(target1);
	Movement_set_M2_pulse_varying(target2);

	FLAG_CLEAR(FLAGS, FLAG_ENCODERS_READY);
}

void Movement_skew_correct(Direction direction)
{
	// Increase the speed of one motor to correct for a skew
	FLAG_SET(FLAGS, FLAG_SKEW_CORRECTING);

	switch (direction)
	{
	case DIRECTION_LEFT:
	{
		Movement_set_M1_pulse_target(MOVEMENT_SPEED_RUN + MOVEMENT_CORRECTION_SKEW);
		break;
	}
	case DIRECTION_RIGHT:
	{
		Movement_set_M2_pulse_target(MOVEMENT_SPEED_RUN + MOVEMENT_CORRECTION_SKEW);
		break;
	}
	default:
	{
		break;
	}
	}
}

void Movement_sync_motors(uint16 speed)
{
	FLAG_CLEAR(FLAGS, FLAG_SKEW_CORRECTING);

	Movement_set_M1_pulse_target(speed);
	Movement_set_M2_pulse_target(speed);
}

void Movement_move_mm(uint16 distance)
{
	// Enable the motors, and set the target distance, turn off move infinitely
	Motor_Control_Reg_Write(Motor_Control_Reg_Read() & ~(1 << MOTOR_DISABLE_CR_POS));
	MOVEMENT_PULSES_TO_MOVE = (float)distance / MOVEMENT_MM_PER_PULSE;

	FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
}

void Movement_write_M1_pulse(uint16 target)
{
	PWM_1_WriteCompare(PWM_1_ReadPeriod() * Movement_calculate_duty(target));
}

void Movement_write_M2_pulse(uint16 target)
{
	PWM_2_WriteCompare(PWM_2_ReadPeriod() * Movement_calculate_duty(target));
}

void Movement_set_M1_pulse_varying(uint16 target)
{
	MOVEMENT_PULSE_VARYING_1 = target;
}

void Movement_set_M2_pulse_varying(uint16 target)
{
	MOVEMENT_PULSE_VARYING_2 = target;
}

void Movement_set_M1_pulse_target(uint16 target)
{
	MOVEMENT_PULSE_TARGET_1 = target;
}

void Movement_set_M2_pulse_target(uint16 target)
{
	MOVEMENT_PULSE_TARGET_2 = target;
}

float Movement_calculate_duty(uint16 target)
{
	float dutyFraction = ((float)target / PWM_1_ReadPeriod());
	if (dutyFraction < 1)
	{
		return dutyFraction;
	}
	else
	{
		return 1;
	}
}

void Movement_turn_left(uint16 angle)
{
	// Disable interrupts so decoders dont get reset to 0
	CYGlobalIntDisable;
	uint16 pulseTarget = Movement_calculate_angle_to_pulse(angle);
	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_set_direction_left(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_TURN);
	Movement_write_M2_pulse(MOVEMENT_SPEED_TURN);

	// Poll until pulse target is met
	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() > -pulseTarget)
	{
		;
	}
	Movement_set_direction_left(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_MOTOR_OFF);
	Movement_write_M2_pulse(MOVEMENT_MOTOR_OFF);

	// Reset decoders to previous value before tur
	QuadDec_M1_SetCounter(pulseMeas);
	CYGlobalIntEnable;
}

void Movement_turn_right(uint16 angle)
{
	CYGlobalIntDisable;
	uint16 pulseTarget = Movement_calculate_angle_to_pulse(angle);
	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_set_direction_right(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_TURN);
	Movement_write_M2_pulse(MOVEMENT_SPEED_TURN);
	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() < pulseTarget)
	{
		;
	}
	Movement_set_direction_right(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_MOTOR_OFF);
	Movement_write_M2_pulse(MOVEMENT_MOTOR_OFF);
	QuadDec_M1_SetCounter(pulseMeas);
	CYGlobalIntEnable;
}

uint16 Movement_calculate_angle_to_pulse(uint16 angle)
{
	switch (angle)
	{
	case 90:
	{
		return MOVEMENT_PULSE_90_DEGREE - MOVEMENT_CORRECTION_TURNS;
	}
	case 180:
	{
		return MOVEMENT_PULSE_180_DEGREE - MOVEMENT_CORRECTION_TURNS;
	}
	default:
	{
		// Convert angle to fraction of circle by dividing 360
		// Multiply fraction by total pivot circumference
		// Divide by circumference of wheel to determine revs needed
		// Convert revs to pulses through multiply 228
		return ((((angle / (float)360) * MOVEMENT_PIVOT_CIRCUMFERENCE) / MOVEMENT_WHEEL_CIRCUMFERENCE) * MOVEMENT_PULSE_REVOLUTION) - MOVEMENT_CORRECTION_TURNS;
	}
	}
}

void Movement_init_motors()
{
	PWM_1_Start();
	PWM_2_Start();
	Timer_Dec_Start();
	QuadDec_M1_Start();
	QuadDec_M2_Start();
	isr_getpulse_StartEx(PROCESS_PULSE);
}

void Movement_set_pwm_1_duty_cycle(uint8 percent)
{
	// set the compare
	uint8 compare = Movement_calculate_compare(percent);
	PWM_1_WriteCompare(compare);
}

void Movement_set_pwm_2_duty_cycle(uint8 percent)
{
	// set the compare
	uint8 compare = Movement_calculate_compare(percent);
	PWM_2_WriteCompare(compare);
}

uint8 Movement_calculate_compare(uint8 percent)
{
	// get max count assuming it is 8 bits
	uint8 maxCount = PWM_2_ReadPeriod();
	uint8 compare = (float)maxCount * ((float)percent / 100);
	return compare;
}

void Movement_set_direction_left(Direction direction)
{
	uint8 currentValue = Motor_Control_Reg_Read();
	switch (direction)
	{
	case DIRECTION_FORWARD:
	{
		currentValue |= 1 << MOTOR_LEFT_CR_POS;
		break;
	}
	case DIRECTION_REVERSE:
	{
		currentValue &= ~(1 << MOTOR_LEFT_CR_POS);
		break;
	}
	default:
		break;
	}
	Motor_Control_Reg_Write(currentValue);
}

void Movement_set_direction_right(Direction direction)
{
	uint8 currentValue = Motor_Control_Reg_Read();
	switch (direction)
	{
	case DIRECTION_FORWARD:
	{
		currentValue |= 1 << MOTOR_RIGHT_CR_POS;
		break;
	}
	case DIRECTION_REVERSE:
	{
		currentValue &= ~(1 << MOTOR_RIGHT_CR_POS);
		break;
	}
	default:
		break;
	}
	Motor_Control_Reg_Write(currentValue);
}

void Movement_set_direction(Direction direction)
{
	Movement_set_direction_left(direction);
	Movement_set_direction_right(direction);
}

void Movement_set_speed_left(uint8 percent)
{
	// While (encoder target < encoder reading){
	// Increase duty cycle
	//}
	Movement_set_pwm_1_duty_cycle(percent);
}

void Movement_set_speed_right(uint8 percent)
{
	Movement_set_pwm_2_duty_cycle(percent);
}

void Movement_set_speed(uint8 percent)
{
	Movement_set_speed_left(percent);
	Movement_set_speed_right(percent);
}
