#include "movement.h"
#include <project.h>

volatile float correction, next_PWM;
CY_ISR(adjustMotors)
{
	APPARENT_PULSE_L = QuadDec_M1_GetCounter();
	APPARENT_PULSE_R = QuadDec_M2_GetCounter();
	CURRENT_PWM_L = PWM_1_ReadCompare();
	CURRENT_PWM_R = PWM_2_ReadCompare();
	// Store pulses in data structure

	TOTAL_PULSE_L += APPARENT_PULSE_L;
	TOTAL_PULSE_R += APPARENT_PULSE_R;

	/* Correction Algorithm:
	 * error = TPL - APL
	 * correction = (error/target * pwmMax)
	 * pwm_writeCompare( PWM_readCompare + correction > pwmMax ? pwmMax : PWM_readCompare + correction)
	 */
	PULSE_ERROR = TARGET_PULSE_L - APPARENT_PULSE_L;
	correction = PULSE_ERROR / TARGET_PULSE_L * PWM_MAX;
	next_PWM = CURRENT_PWM_L + correction > PWM_MAX ? PWM_MAX : CURRENT_PWM_L + correction;
	PWM_1_WriteCompare(next_PWM);

	PULSE_ERROR = TARGET_PULSE_R - APPARENT_PULSE_R;
	correction = PULSE_ERROR / TARGET_PULSE_R * PWM_MAX;
	next_PWM = CURRENT_PWM_R + correction > PWM_MAX ? PWM_MAX : CURRENT_PWM_R + correction;
	PWM_2_WriteCompare(next_PWM);

	QuadDec_M1_SetCounter(0);
	QuadDec_M2_SetCounter(0);
	Timer_Motor_Control_ReadStatusRegister();
}

void init_control_loop()
{
	Timer_Motor_Control_Start();
	isr_adjust_motors_StartEx(adjustMotors);
}

void set_target_pulse_L(uint8_t target)
{
	TARGET_PULSE_L = target;
}

void set_target_pulse_R(uint8_t target)
{
	TARGET_PULSE_R = target;
}

void Movement_set_pwm_1_duty_cycle(uint8_t percent)
{
	// set the compare
	uint8_t compare = Movement_calculate_compare(percent);
	PWM_1_WriteCompare(compare);
}

void Movement_set_pwm_2_duty_cycle(uint8_t percent)
{
	// set the compare
	uint8_t compare = Movement_calculate_compare(percent);
	PWM_2_WriteCompare(compare);
}

uint8_t Movement_calculate_compare(uint8_t percent)
{
	// get max count assuming it is 8 bits
	uint8_t maxCount = PWM_2_ReadPeriod();
	uint8_t compare = (float)maxCount * ((float)percent / 100);
	return compare;
}

void Movement_set_direction_left(Direction direction)
{
	uint8_t currentValue = Dir_Control_Reg_Read();
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
	uint8_t currentValue = Dir_Control_Reg_Read();
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

// TODO: Change percent to encoder pulses and raise power accordingly
void Movement_set_speed_left(uint8_t percent)
{
	// While (encoder target < encoder reading){
	// Increase duty cycle
	//}
	Movement_set_pwm_1_duty_cycle(percent);
}

void Movement_set_speed_right(uint8_t percent)
{
	Movement_set_pwm_2_duty_cycle(percent);
}

void Movement_set_speed(uint8_t percent)
{
	Movement_set_speed_left(percent);
	Movement_set_speed_right(percent);
}