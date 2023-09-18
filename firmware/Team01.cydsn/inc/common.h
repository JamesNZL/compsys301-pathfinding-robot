#ifndef COMMON_H_
#define COMMON_H_

#include <cytypes.h>

/*
 * Null
 */
#define NULL ((void *)0)

/*
 * Booleans
 */
#define bool	uint8

#define FALSE	0
#define TRUE	1
#define UNKNOWN 10

/*
 * Flag Bits
 */
volatile extern uint8 FLAGS;

#define FLAG_USB_INPUT			 0
#define FLAG_ENCODERS_READY		 1
#define FLAG_SKEW_CORRECTING	 2
#define FLAG_MOVE_INFINITELY	 3
#define FLAG_SENSOR_AWAIT_RISING 4

/**
 * @brief Check whether a flag bit is set.
 *
 * @param flags The flag byte(s).
 * @param bit The position of the flag bit.
 */
#define FLAG_IS_SET(flags, bit) flags & (1 << bit)

/**
 * @brief Check whether a flag bit is cleared.
 *
 * @param flags The flag byte(s).
 * @param bit The position of the flag bit.
 */
#define FLAG_IS_CLEARED(flags, bit) ~flags & (1 << bit)

/**
 * @brief Set a flag bit.
 *
 * @param flags The flag byte(s).
 * @param bit The position of the flag bit.
 */
#define FLAG_SET(flags, bit) flags |= (1 << bit)

/**
 * @brief Clear a flag bit.
 *
 * @param flags The flag byte(s).
 * @param bit The position of the flag bit.
 */
#define FLAG_CLEAR(flags, bit) flags &= ~(1 << bit)

/*
 * Debugging
 */
#define LED_ON		   LED_Write(1)
#define LED_OFF		   LED_Write(0)
#define LED_TOGGLE	   LED_Write(~LED_Read())

#define DB0_ON		   DB0_Write(1)
#define DB0_OFF		   DB0_Write(0)
#define DB0_TOGGLE_LED DB0_Write(~DB0_Read())

#define DB1_ON		   DB1_Write(1)
#define DB1_OFF		   DB1_Write(0)
#define DB1_TOGGLE_LED DB1_Write(~DB1_Read())

#define DB2_ON		   DB2_Write(1)
#define DB2_OFF		   DB2_Write(0)
#define DB2_TOGGLE_LED DB2_Write(~DB2_Read())

#define DB3_ON		   DB3_Write(1)
#define DB3_OFF		   DB3_Write(0)
#define DB3_TOGGLE_LED DB3_Write(~DB3_Read())

#define DB4_ON		   DB4_Write(1)
#define DB4_OFF		   DB4_Write(0)
#define DB4_TOGGLE_LED DB4_Write(~DB4_Read())

#define DB5_ON		   DB5_Write(1)
#define DB5_OFF		   DB5_Write(0)
#define DB5_TOGGLE_LED DB5_Write(~DB5_Read())

#define DB6_ON		   DB6_Write(1)
#define DB6_OFF		   DB6_Write(0)
#define DB6_TOGGLE_LED DB6_Write(~DB6_Read())

#define DB7_ON		   DB7_Write(1)
#define DB7_OFF		   DB7_Write(0)
#define DB7_TOGGLE_LED DB7_Write(~DB7_Read())

#endif