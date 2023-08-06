#include "movement.h"
#include <project.h>

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

void Movement_set_speed_left(uint8_t percent)
{
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