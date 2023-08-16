#include "movement.h"
#include "common.h"
#include <project.h>

void MOVEMENT_set_M1_pulse(uint16_t target)
{
	PWM_1_WriteCompare(PWM_1_ReadPeriod() * ((target + 170.9) / 8.6543) / (float)100);
}

void MOVEMENT_set_M2_pulse(uint16_t target)
{
	PWM_2_WriteCompare(PWM_2_ReadPeriod() * ((target + 170.9) / 8.6543) / (float)100);
}

void MOVEMENT_set_pwm_1_duty_cycle(uint8_t percent)
{
	// set the compare
	uint8_t compare = MOVEMENT_calculate_compare(percent);
	PWM_1_WriteCompare(compare);
}

void MOVEMENT_set_pwm_2_duty_cycle(uint8_t percent)
{
	// set the compare
	uint8_t compare = MOVEMENT_calculate_compare(percent);
	PWM_2_WriteCompare(compare);
}

uint8_t MOVEMENT_calculate_compare(uint8_t percent)
{
	// get max count assuming it is 8 bits
	uint8_t maxCount = PWM_2_ReadPeriod();
	uint8_t compare = (float)maxCount * ((float)percent / 100);
	return compare;
}

void MOVEMENT_set_direction_left(Direction direction)
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

void MOVEMENT_set_direction_right(Direction direction)
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

void MOVEMENT_set_direction(Direction direction)
{
	MOVEMENT_set_direction_left(direction);
	MOVEMENT_set_direction_right(direction);
}

// TODO: Change percent to encoder pulses and raise power accordingly
void MOVEMENT_set_speed_left(uint8_t percent)
{
	// While (encoder target < encoder reading){
	// Increase duty cycle
	//}
	MOVEMENT_set_pwm_1_duty_cycle(percent);
}

void MOVEMENT_set_speed_right(uint8_t percent)
{
	MOVEMENT_set_pwm_2_duty_cycle(percent);
}

void MOVEMENT_set_speed(uint8_t percent)
{
	MOVEMENT_set_speed_left(percent);
	MOVEMENT_set_speed_right(percent);
}