#ifndef BATTERY_H_
#define BATTERY_H_

#include <cytypes.h>

#define BATTERY_COUNT			6
#define BATTERY_FULL_MV			1300 * BATTERY_COUNT
#define BATTERY_EMPTY_MV		1250 * BATTERY_COUNT

#define BATTERY_DIVIDER_GAIN	4.7037037037f // 10k 2k7 resistive divider

#define BATTERY_SAMPLES_COUNT	10
#define BATTERY_LOW_FLASH_COUNT 255 // must fit in a uint8

/**
 * @brief Display the battery level the debugging LEDs.
 *
 * @return uint16 The current battery voltage.
 */
uint16 Battery_display_level(void);

#endif