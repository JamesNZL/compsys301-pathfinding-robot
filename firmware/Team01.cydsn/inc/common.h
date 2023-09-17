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
#define FLAG_WAITING_AFTER_TURN	 5

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
#define LED_ON	   LED_Write(1)
#define LED_OFF	   LED_Write(0)
#define LED_TOGGLE LED_Write(~LED_Read())

#define DB0_ON	   DB0_Write(1)
#define DB0_OFF	   DB0_Write(0)
#define DB0_TOGGLE DB0_Write(~DB0_Read())

#define DB1_ON	   DB1_Write(1)
#define DB1_OFF	   DB1_Write(0)
#define DB1_TOGGLE DB1_Write(~DB1_Read())

#define DB2_ON	   DB2_Write(1)
#define DB2_OFF	   DB2_Write(0)
#define DB2_TOGGLE DB2_Write(~DB2_Read())

#define DB3_ON	   DB3_Write(1)
#define DB3_OFF	   DB3_Write(0)
#define DB3_TOGGLE DB3_Write(~DB3_Read())

#define DB4_ON	   DB4_Write(1)
#define DB4_OFF	   DB4_Write(0)
#define DB4_TOGGLE DB4_Write(~DB4_Read())

#define DB5_ON	   DB5_Write(1)
#define DB5_OFF	   DB5_Write(0)
#define DB5_TOGGLE DB5_Write(~DB5_Read())

#define DB6_ON	   DB6_Write(1)
#define DB6_OFF	   DB6_Write(0)
#define DB6_TOGGLE DB6_Write(~DB6_Read())

#define DB7_ON	   DB7_Write(1)
#define DB7_OFF	   DB7_Write(0)
#define DB7_TOGGLE DB7_Write(~DB7_Read())

#define DB_LEFT_ON \
	DB0_ON;        \
	DB1_ON;        \
	DB2_ON;        \
	DB3_ON

#define DB_RIGHT_ON \
	DB4_ON;         \
	DB5_ON;         \
	DB6_ON;         \
	DB7_ON

#define DB_EVEN_ON \
	DB0_ON;        \
	DB2_ON;        \
	DB4_ON;        \
	DB6_ON

#define DB_ODD_ON \
	DB1_ON;       \
	DB3_ON;       \
	DB5_ON;       \
	DB7_ON

#define DB_ALL_ON \
	DB_LEFT_ON;   \
	DB_RIGHT_ON

#define DB_ALL_OFF \
	DB0_OFF;       \
	DB1_OFF;       \
	DB2_OFF;       \
	DB3_OFF;       \
	DB4_OFF;       \
	DB5_OFF;       \
	DB6_OFF;       \
	DB7_OFF

#define DB_ALL_TOGGLE \
	DB0_TOGGLE;       \
	DB1_TOGGLE;       \
	DB2_TOGGLE;       \
	DB3_TOGGLE;       \
	DB4_TOGGLE;       \
	DB5_TOGGLE;       \
	DB6_TOGGLE;       \
	DB7_TOGGLE

#endif