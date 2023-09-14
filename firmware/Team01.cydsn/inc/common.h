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

#define FLAG_USB_INPUT				0
#define FLAG_ENCODERS_READY			1
#define FLAG_SKEW_CORRECTING		2
#define FLAG_MOVE_INFINITELY		3

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

#endif