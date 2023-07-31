#include "movement.h"
#include <project.h>

void set_pwm_1_duty_cycle(uint8_t percent)
{
    // get max count assuming it is 8 bits
    uint8 maxCount = PWM_1_ReadPeriod();
    // set the compare
    uint8 compare = maxCount - (float)maxCount * ((float)percent / 100);
    PWM_1_WriteCompare(compare);
}

void set_pwm_2_duty_cycle(uint8_t percent)
{
    // get max count assuming it is 8 bits
    uint8 maxCount = PWM_2_ReadPeriod();
    // set the compare
    uint8 compare = maxCount - (float)maxCount * ((float)percent / 100);
    PWM_2_WriteCompare(compare);
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