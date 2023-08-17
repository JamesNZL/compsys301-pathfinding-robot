#include "movement.h"
#include "common.h"
#include <project.h>

volatile float OFFSET = 170.9;
volatile float SLOPE = 8.6543;

void Movement_set_M1_pulse(uint16 target)
{
	PWM_1_WriteCompare(PWM_1_ReadPeriod() * ((target + OFFSET) / SLOPE) / (float)100);
}

void Movement_set_M2_pulse(uint16 target)
{
	PWM_2_WriteCompare(PWM_2_ReadPeriod() * ((target + OFFSET) / SLOPE) / (float)100);
}

void Movement_turn_left(uint16 angle)
{
	// OPTIONAL - OPTIMIZATION
	// Quick switch case for common turns 90 degree and 180 degree to skip long calculations

	// Convert angle to fraction of circumference by dividing 360
	// Multiply fraction by total circumference
	// Divide by circumference of wheel to determine revs needed
	// Convert revs to pulses through multiply 228

	// Poll to wait until pulse target is met
	// Exit loop
	// Set both motors forward
	// OPTIONAL: Store working rpm and return to it - #define CONSTANT_SPEED 400
}

void Movement_turn_right(uint16 angle)
{
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