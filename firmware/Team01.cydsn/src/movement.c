#include "movement.h"
#include "common.h"
#include <project.h>

const uint8 MOVEMENT_BRAKE_SPEED = 150;
uint16 MOVEMENT_RUN_SPEED = 300;
const uint16 MOVEMENT_MOTOR_TURN_SPEED = 300;
const uint8 MOVEMENT_CORRECTION_INCREASE = 10;
const uint8 MOVEMENT_PULSE_CORRECTION = 9;
const uint8 Kp = 1;

CY_ISR(PROCESS_PULSE)
{
	MOVEMENT_APPARENT_PULSE_1 = QuadDec_M1_GetCounter();
	MOVEMENT_APPARENT_PULSE_2 = QuadDec_M2_GetCounter();

	FLAGS |= (1 << FLAG_ENCODERS_READY);

	QuadDec_M1_SetCounter(0);
	QuadDec_M2_SetCounter(0);
	Timer_Dec_ReadStatusRegister();
}

uint16 Movement_cm_to_pulse(float cms)
{
	return (uint16)(cms * MOVEMENT_CMS_CONVERSION);
}

void Movement_check_dist()
{
	if (FLAG_IS_CLEARED(FLAGS, FLAG_MOVE_INFINITELY))
	{
		if (MOVEMENT_PULSES_TO_MOVE <= 0)
		{
			Movement_set_M1_pulse_target(MOVEMENT_MOTOR_OFF);
			Movement_set_M2_pulse_target(MOVEMENT_MOTOR_OFF);
			Motor_Control_Reg_Write(Motor_Control_Reg_Read() | (1 << MOTOR_DISABLE_CR_POS));
		}
		else if (MOVEMENT_PULSES_TO_MOVE < 150)
		{
			Movement_set_M1_pulse_target(MOVEMENT_BRAKE_SPEED);
			Movement_set_M2_pulse_target(MOVEMENT_BRAKE_SPEED);
		}
	}
}

void Movement_next_control_cycle()
{
	if (FLAG_IS_SET(FLAGS, FLAG_ENCODERS_READY))
	{
		// Subtract read pulses from distance to travel
		if (MOVEMENT_PULSES_TO_MOVE > 0)
		{
			MOVEMENT_PULSES_TO_MOVE -= MOVEMENT_APPARENT_PULSE_1;
		}

		// Samples taken every 25th of a second. Divide target by 25 to get expected 25th of a second pulses
		int8 pulseError1 = (MOVEMENT_PULSE_TARGET_1 / 25) - MOVEMENT_APPARENT_PULSE_1;
		int8 pulseError2 = (MOVEMENT_PULSE_TARGET_2 / 25) - MOVEMENT_APPARENT_PULSE_2;
		// int8 pulseError2 = MOVEMENT_APPARENT_PULSE_1 - MOVEMENT_APPARENT_PULSE_2; // For shimmy shimmy

		uint16 target1 = MOVEMENT_PULSE_VARYING_1 + pulseError1;
		uint16 target2 = MOVEMENT_PULSE_VARYING_2 + pulseError2;

		Movement_write_M1_pulse(target1);
		Movement_write_M2_pulse(target2);

		// Make the varying pulses change up or down accordingly to the observed speed
		Movement_set_M1_pulse_varying(target1);
		Movement_set_M2_pulse_varying(target2);

		FLAGS &= ~(1 << FLAG_ENCODERS_READY);
	}
}

void Movement_skewer(Direction direction)
{
	// Increase the speed of one motor to correct for a skew
	FLAGS |= (1 << FLAG_SKEW_CORRECTING);
	switch (direction)
	{
	case DIRECTION_LEFT:
		Movement_set_M1_pulse_target(MOVEMENT_RUN_SPEED + MOVEMENT_CORRECTION_INCREASE);
		break;
	case DIRECTION_RIGHT:
		Movement_set_M2_pulse_target(MOVEMENT_RUN_SPEED + MOVEMENT_CORRECTION_INCREASE);
		break;
	default:
		break;
	}
}

void Movement_sync_motors(uint16 speed)
{
	FLAGS &= ~(1 << FLAG_SKEW_CORRECTING);
	Movement_set_M1_pulse_target(speed);
	Movement_set_M2_pulse_target(speed);
}

void Movement_move_mm(uint16 dist)
{
	// Enable the motors, and set the target distance, turn off move infinitely
	Motor_Control_Reg_Write(Motor_Control_Reg_Read() & ~(1 << MOTOR_DISABLE_CR_POS));
	MOVEMENT_PULSES_TO_MOVE = (float)dist / MOVEMENT_MM_PER_PULSE;
	FLAGS &= ~(1 << FLAG_MOVE_INFINITELY);
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
	Movement_write_M1_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	Movement_write_M2_pulse(MOVEMENT_MOTOR_TURN_SPEED);

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
	Movement_write_M1_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	Movement_write_M2_pulse(MOVEMENT_MOTOR_TURN_SPEED);
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
		return MOVEMENT_PULSE_90_DEGREE - MOVEMENT_PULSE_CORRECTION;
	case 180:
		return MOVEMENT_PULSE_180_DEGREE - MOVEMENT_PULSE_CORRECTION;
	default:
		// Convert angle to fraction of circle by dividing 360
		// Multiply fraction by total pivot circumference
		// Divide by circumference of wheel to determine revs needed
		// Convert revs to pulses through multiply 228
		return ((((angle / (float)360) * MOVEMENT_PIVOT_CIRCUMFERENCE) / MOVEMENT_WHEEL_CIRCUMFERENCE) * MOVEMENT_PULSE_REVOLUTION) - MOVEMENT_PULSE_CORRECTION;
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
