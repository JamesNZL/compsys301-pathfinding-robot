#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
    
/*
 * Booleans
 */
#define FALSE	0
#define TRUE	1
#define UNKNOWN 10

/*
 * Flag Bits
 */
volatile extern uint8_t FLAGS;

#define IS_SET(byte, bit)	  byte & (1 << bit)
#define IS_CLEARED(byte, bit) ~byte & (1 << bit)

#define FLAG_USB_INPUT		  0

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