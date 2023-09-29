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
volatile extern uint16 FLAGS;

#define FLAG_USB_INPUT				  0
#define FLAG_ENCODERS_READY			  1
#define FLAG_SKEW_CORRECTING		  2
#define FLAG_MOVE_INFINITELY		  3
#define FLAG_SENSOR_AWAIT_RISING	  4
#define FLAG_WAITING_AFTER_ACTION	  5
#define FLAG_ON_FINAL_STRETCH		  6
#define FLAG_WAITING_FOR_FINAL_ACTION 7
#define FLAG_TOGGLE_TURN_TIMEOUT	  8

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

#define DEBUG_0_ON	   DEBUG_0_Write(1)
#define DEBUG_0_OFF	   DEBUG_0_Write(0)
#define DEBUG_0_TOGGLE DEBUG_0_Write(~DEBUG_0_Read())

#define DEBUG_1_ON	   DEBUG_1_Write(1)
#define DEBUG_1_OFF	   DEBUG_1_Write(0)
#define DEBUG_1_TOGGLE DEBUG_1_Write(~DEBUG_1_Read())

#define DEBUG_2_ON	   DEBUG_2_Write(1)
#define DEBUG_2_OFF	   DEBUG_2_Write(0)
#define DEBUG_2_TOGGLE DEBUG_2_Write(~DEBUG_2_Read())

#define DEBUG_3_ON	   DEBUG_3_Write(1)
#define DEBUG_3_OFF	   DEBUG_3_Write(0)
#define DEBUG_3_TOGGLE DEBUG_3_Write(~DEBUG_3_Read())

#define DEBUG_4_ON	   DEBUG_4_Write(1)
#define DEBUG_4_OFF	   DEBUG_4_Write(0)
#define DEBUG_4_TOGGLE DEBUG_4_Write(~DEBUG_4_Read())

#define DEBUG_5_ON	   DEBUG_5_Write(1)
#define DEBUG_5_OFF	   DEBUG_5_Write(0)
#define DEBUG_5_TOGGLE DEBUG_5_Write(~DEBUG_5_Read())

#define DEBUG_6_ON	   DEBUG_6_Write(1)
#define DEBUG_6_OFF	   DEBUG_6_Write(0)
#define DEBUG_6_TOGGLE DEBUG_6_Write(~DEBUG_6_Read())

#define DEBUG_7_ON	   DEBUG_7_Write(1)
#define DEBUG_7_OFF	   DEBUG_7_Write(0)
#define DEBUG_7_TOGGLE DEBUG_7_Write(~DEBUG_7_Read())

#define DEBUG_LEFT_ON \
	DEBUG_0_ON;       \
	DEBUG_1_ON;       \
	DEBUG_2_ON;       \
	DEBUG_3_ON

#define DEBUG_RIGHT_ON \
	DEBUG_4_ON;        \
	DEBUG_5_ON;        \
	DEBUG_6_ON;        \
	DEBUG_7_ON

#define DEBUG_EVEN_ON \
	DEBUG_0_ON;       \
	DEBUG_2_ON;       \
	DEBUG_4_ON;       \
	DEBUG_6_ON

#define DEBUG_ODD_ON \
	DEBUG_1_ON;      \
	DEBUG_3_ON;      \
	DEBUG_5_ON;      \
	DEBUG_7_ON

#define DEBUG_OUTER_ON \
	DEBUG_0_ON;        \
	DEBUG_3_ON;        \
	DEBUG_4_ON;        \
	DEBUG_7_ON

#define DEBUG_INNER_ON \
	DEBUG_1_ON;        \
	DEBUG_2_ON;        \
	DEBUG_5_ON;        \
	DEBUG_6_ON

#define DEBUG_UPPER_ON \
	DEBUG_0_ON;        \
	DEBUG_1_ON;        \
	DEBUG_4_ON;        \
	DEBUG_5_ON

#define DEBUG_LOWER_ON \
	DEBUG_2_ON;        \
	DEBUG_3_ON;        \
	DEBUG_6_ON;        \
	DEBUG_7_ON

#define DEBUG_ALL_ON \
	DEBUG_LEFT_ON;   \
	DEBUG_RIGHT_ON

#define DEBUG_LEFT_OFF \
	DEBUG_0_OFF;       \
	DEBUG_1_OFF;       \
	DEBUG_2_OFF;       \
	DEBUG_3_OFF

#define DEBUG_RIGHT_OFF \
	DEBUG_4_OFF;        \
	DEBUG_5_OFF;        \
	DEBUG_6_OFF;        \
	DEBUG_7_OFF

#define DEBUG_ALL_OFF \
	DEBUG_0_OFF;      \
	DEBUG_1_OFF;      \
	DEBUG_2_OFF;      \
	DEBUG_3_OFF;      \
	DEBUG_4_OFF;      \
	DEBUG_5_OFF;      \
	DEBUG_6_OFF;      \
	DEBUG_7_OFF

#define DEBUG_ALL_TOGGLE \
	DEBUG_0_TOGGLE;      \
	DEBUG_1_TOGGLE;      \
	DEBUG_2_TOGGLE;      \
	DEBUG_3_TOGGLE;      \
	DEBUG_4_TOGGLE;      \
	DEBUG_5_TOGGLE;      \
	DEBUG_6_TOGGLE;      \
	DEBUG_7_TOGGLE

#endif