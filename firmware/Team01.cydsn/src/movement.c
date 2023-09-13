#include "movement.h"
#include "common.h"
#include <project.h>

volatile const float MOVEMENT_OFFSET = 170.9;
volatile const float MOVEMENT_SLOPE = 8.6543;

const uint8 MOVEMENT_BRAKE_SPEED = 150;
const uint16 MOVEMENT_RUN_SPEED = 300;
const uint16 MOVEMENT_MOTOR_TURN_SPEED = 227;
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

void Movement_move_mm(uint16 dist)
{
	MOVEMENT_PULSES_TO_MOVE = (float)dist / MOVEMENT_MM_PER_PULSE;
	Movement_set_M1_ctrltarget(MOVEMENT_RUN_SPEED);
	Movement_set_M2_ctrltarget(MOVEMENT_RUN_SPEED);
	MOVEMENT_CPULSE_1 = MOVEMENT_RUN_SPEED;
	MOVEMENT_CPULSE_2 = MOVEMENT_RUN_SPEED;
}

void Movement_set_M1_pulse(uint16 target)
{
	PWM_1_WriteCompare(PWM_1_ReadPeriod() * Movement_calculate_duty(target));
}

void Movement_set_M2_pulse(uint16 target)
{
	PWM_2_WriteCompare(PWM_2_ReadPeriod() * Movement_calculate_duty(target));
}

void Movement_set_M1_ctrltarget(uint16 target)
{
	MOVEMENT_TPULSE_1 = target;
}

void Movement_set_M2_ctrltarget(uint16 target)
{
	MOVEMENT_TPULSE_2 = target;
}

float Movement_calculate_duty(uint16 target)
{
	float dutyFraction = (((target + MOVEMENT_OFFSET) / MOVEMENT_SLOPE) / (float)100);
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
	CYGlobalIntDisable;
	uint16 pulseTarget = Movement_calculate_angle_to_pulse(angle);
	// uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_set_direction_left(DIRECTION_REVERSE);
	Movement_set_M1_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	Movement_set_M2_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() > -pulseTarget)
	{
		;
	}
	Movement_set_direction_left(DIRECTION_FORWARD);
	Movement_set_M1_pulse(MOVEMENT_MOTOR_OFF);
	Movement_set_M2_pulse(MOVEMENT_MOTOR_OFF);
	CYGlobalIntEnable;
}

void Movement_turn_right(uint16 angle)
{
	CYGlobalIntDisable;
	uint16 pulseTarget = Movement_calculate_angle_to_pulse(angle);
	// uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_set_direction_right(DIRECTION_REVERSE);
	Movement_set_M1_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	Movement_set_M2_pulse(MOVEMENT_MOTOR_TURN_SPEED);
	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() < pulseTarget)
	{
		;
	}
	Movement_set_direction_right(DIRECTION_FORWARD);
	Movement_set_M1_pulse(MOVEMENT_MOTOR_OFF);
	Movement_set_M2_pulse(MOVEMENT_MOTOR_OFF);
	CYGlobalIntEnable;
}

uint16 Movement_calculate_angle_to_pulse(uint16 angle)
{
	uint16 pulseTarget;
	switch (angle)
	{
	case 90:
		pulseTarget = MOVEMENT_PULSE_90_DEGREE - MOVEMENT_PULSE_CORRECTION;
		break;
	case 180:
		pulseTarget = MOVEMENT_PULSE_180_DEGREE - MOVEMENT_PULSE_CORRECTION;
		break;
	default:
		// Convert angle to fraction of circle by dividing 360
		// Multiply fraction by total pivot circumference
		// Divide by circumference of wheel to determine revs needed
		// Convert revs to pulses through multiply 228
		pulseTarget = ((((angle / (float)360) * MOVEMENT_PIVOT_CIRCUMFERENCE) / MOVEMENT_WHEEL_CIRCUMFERENCE) * MOVEMENT_PULSE_REVOLUTION) - MOVEMENT_PULSE_CORRECTION;
	}
	return pulseTarget;
}

void Movement_init_decoder_ISR()
{
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
	uint8 currentValue = Dir_Control_Reg_Read();
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
	}
	Dir_Control_Reg_Write(currentValue);
}

void Movement_set_direction_right(Direction direction)
{
	uint8 currentValue = Dir_Control_Reg_Read();
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
	}
	Dir_Control_Reg_Write(currentValue);
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
