#include "movement.h"
#include <project.h>

void set_pwm_1_duty_cycle(uint8_t percent)
{
    // set the compare
    uint8_t compare = calculate_compare(percent);
    PWM_1_WriteCompare(compare);
}

void set_pwm_2_duty_cycle(uint8_t percent)
{
    // set the compare
    uint8_t compare = calculate_compare(percent);
    PWM_2_WriteCompare(compare);
}

uint8_t calculate_compare(uint8_t percent)
{
    // get max count assuming it is 8 bits
    uint8_t maxCount = PWM_2_ReadPeriod();
    uint8_t compare = (float)maxCount * ((float)percent / 100);
    return compare;
}

void set_direction_left(Direction direction)
{
    uint8_t currentValue = Dir_Control_Reg_Read();
    switch (direction)
    {
    case FORWARD:
    {
        currentValue |= 1 << LEFT_MOTOR_CR_POS;
        break;
    }
    case REVERSE:
    {
        currentValue &= ~(1 << LEFT_MOTOR_CR_POS);
        break;
    }
    }
    Dir_Control_Reg_Write(currentValue);
}

void set_direction_right(Direction direction)
{
    uint8_t currentValue = Dir_Control_Reg_Read();
    switch (direction)
    {
    case FORWARD:
    {
        currentValue |= 1 << RIGHT_MOTOR_CR_POS;
        break;
    }
    case REVERSE:
    {
        currentValue &= ~(1 << RIGHT_MOTOR_CR_POS);
        break;
    }
    }
    Dir_Control_Reg_Write(currentValue);
}

void set_direction(Direction direction)
{
    set_direction_left(direction);
    set_direction_right(direction);
}

void set_speed_left(uint8_t percent)
{
    set_pwm_1_duty_cycle(percent);
}

void set_speed_right(uint8_t percent)
{
    set_pwm_2_duty_cycle(percent);
}

void set_speed(uint8_t percent)
{
    set_speed_left(percent);
    set_speed_right(percent);
}