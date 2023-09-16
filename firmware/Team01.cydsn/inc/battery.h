#ifndef BATTERY_H_
#define BATTERY_H_

#define BATTERY_COUNT	 6
#define BATTERY_FULL_MV	 1400 * BATTERY_COUNT
#define BATTERY_EMPTY_MV 1100 * BATTERY_COUNT

void Battery_display_level(void);

#endif