#include "sensor.h"

// Samples the sensor information and stores it for later processing
#define SENSOR_SAMPLE_READING(sensorStruct, sensorReadFunction) \
	if (sensorReadFunction())                                   \
	{                                                           \
		sensorStruct.highWasSampled = TRUE;                     \
	}

// Debounces (ensures the signal has held its value for at least X periods) and stores the required status
#define SENSOR_DEBOUNCE_AND_UPDATE_STATUS(sensorStruct)              \
	sensorStruct.periodCount++;                                      \
	bool sensorStruct##newStatus = sensorStruct.highWasSampled;      \
	if (sensorStruct.previousStatus != sensorStruct##newStatus)      \
	{                                                                \
		sensorStruct.periodCount = 0;                                \
	}                                                                \
	if (sensorStruct.periodCount >= SENSOR_MINIMUM_DEBOUNCE_PERIODS) \
	{                                                                \
		sensorStruct.status = sensorStruct##newStatus;               \
	}                                                                \
	sensorStruct.highWasSampled = FALSE;                             \
	sensorStruct.previousStatus = sensorStruct##newStatus;

#define SENSOR_WRITE_LOW(sensorStruct) \
	sensorStruct.status = FALSE

#define SENSOR_WRITE_HIGH(sensorStruct) \
	sensorStruct.status = TRUE

/**
 * @brief Undertakes the required steps to reset and set the timer period
 * @param period a valid period for a 16-bit UDB timer
 */
static void Sensor_set_light_check_timer_period(uint16 period);

/**
 * @brief reset and configure for enabling the light sense isr
 */
static void Sensor_prepare_for_next_rising_edge(void);
/**
 * @brief procedure for when there is no rising edge withing a specific timeframe
 */
static void Sensor_handle_missing_rising_edge(void);

/**
 * @brief reset and configure for enabline the light check isr for sampling
 */
static void Sensor_prepare_for_sampling(void);
/**
 * @brief read and count occurences of sensor statuses
 */
static void Sensor_sample_sensor_readings(void);
/**
 * @brief Stores the status of all sensors by reading their pins
 */
static void Sensor_debounce_and_update_sensor_statuses(void);

/**
 * @brief sets the status of all sensor structs to FALSE (low)
 */
static void Sensor_write_low_all_sensors(void);

typedef struct Sensor
{
	bool status;
	bool previousStatus;
	bool highWasSampled;
	uint8 periodCount;
} Sensor;

volatile Sensor Sensor_turnLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_turnRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewBackRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewBackLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewFrontRight = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewFrontLeft = SENSOR_DEFAULT_INITIALISATION;
volatile Sensor Sensor_skewMiddle = SENSOR_DEFAULT_INITIALISATION;

volatile uint8 Sensor_sampledPeriods = 0;

CY_ISR(SENSOR_ISR_LIGHT_SENSED)
{
	Sensor_prepare_for_sampling();
}

CY_ISR(SENSOR_ISR_CHECK_LIGHT)
{
	// If we have exceeded the maximum time without a rising edge
	if (FLAG_IS_SET(FLAGS, FLAG_SENSOR_AWAIT_RISING))
	{
		Sensor_handle_missing_rising_edge();
		return;
	}

	// SAMPLING
	Sensor_sample_sensor_readings();
	Sensor_sampledPeriods++;

	// We have taken all samples needed for this rising edge
	if (Sensor_sampledPeriods >= SENSOR_SAMPLING_PERIODS)
	{
		Sensor_prepare_for_next_rising_edge();
		return;
	}
}

SensorActions Sensor_determine_action(void)
{
	uint8 bitfield = ((Sensor_skewMiddle.status << SENSOR_SKEW_MIDDLE_POSITION)
		| (Sensor_skewFrontLeft.status << SENSOR_SKEW_FRONT_LEFT_POSITION)
		| (Sensor_skewFrontRight.status << SENSOR_SKEW_FRONT_RIGHT_POSITION)
		| (Sensor_skewBackLeft.status << SENSOR_SKEW_BACK_LEFT_POSITION)
		| (Sensor_skewBackRight.status << SENSOR_SKEW_BACK_RIGHT_POSITION)
		| (Sensor_turnLeft.status << SENSOR_TURN_LEFT_POSITION)
		| (Sensor_turnRight.status << SENSOR_TURN_RIGHT_POSITION));

	return SENSOR_ACTION_LUT[bitfield];
}

bool Sensor_is_all_sensors_off(void)
{
	return !(
		Sensor_turnLeft.status
		|| Sensor_turnRight.status
		|| Sensor_skewBackRight.status
		|| Sensor_skewBackLeft.status
		|| Sensor_skewMiddle.status
		|| Sensor_skewFrontLeft.status
		|| Sensor_skewFrontRight.status);
}

bool Sensor_is_on_right_turn_intersection(void)
{
	return Sensor_turnLeft.status && !Sensor_turnRight.status;
}

bool Sensor_is_on_left_turn_intersection(void)
{
	return !Sensor_turnLeft.status && Sensor_turnRight.status;
}

bool Sensor_is_on_all_turn_intersection(void)
{
	return !Sensor_turnLeft.status && !Sensor_turnRight.status;
}

bool Sensor_is_middle_on_line(void)
{
	return !Sensor_skewMiddle.status;
}

bool Sensor_has_turn(void)
{
	return !Sensor_turnLeft.status || !Sensor_turnRight.status;
}
bool Sensor_has_right_turn(void)
{
	return !Sensor_turnRight.status;
}
bool Sensor_has_left_turn(void)
{
	return !Sensor_turnLeft.status;
}

bool Sensor_is_any_front_on_line(void)
{
	return (!Sensor_skewFrontLeft.status) || (!Sensor_skewFrontRight.status);
}

bool Sensor_is_both_front_on_line(void)
{
	return (!Sensor_skewFrontLeft.status) && (!Sensor_skewFrontRight.status);
}

bool Sensor_is_any_back_on_line(void)
{
	return (!Sensor_skewBackLeft.status) || (!Sensor_skewBackRight.status);
}

bool Sensor_are_skew_diagonals_on_line(void)
{
	return (((!Sensor_skewBackLeft.status) && (!Sensor_skewFrontRight.status)) || ((!Sensor_skewBackRight.status) && (!Sensor_skewFrontLeft.status)));
}

void Sensor_set_bias_level(float voltage)
{
	uint8_t dacValue = (voltage)*255;

	DAC_Lower_SetValue(dacValue);
	DAC_Middle_SetValue(dacValue);
	DAC_Upper_SetValue(dacValue);
}

void Sensor_write_statuses_to_debug(void)
{
	DEBUG_0_Write(Sensor_skewFrontLeft.status);
	DEBUG_1_Write(Sensor_turnLeft.status);
	DEBUG_2_Write(Sensor_skewBackLeft.status);
	DEBUG_3_Write(Sensor_skewMiddle.status);
	DEBUG_4_Write(Sensor_skewFrontRight.status);
	DEBUG_5_Write(Sensor_turnRight.status);
	DEBUG_6_Write(Sensor_skewBackRight.status);
}

static void Sensor_set_light_check_timer_period(uint16 period)
{
	Timer_Light_Check_Stop();
	Timer_Light_Check_WritePeriod(period);
	Timer_Light_Check_WriteCounter(period);
	Timer_Light_Check_Start();
}

static void Sensor_prepare_for_next_rising_edge(void)
{
	Sensor_debounce_and_update_sensor_statuses();
	Sensor_sampledPeriods = 0;
	FLAG_SET(FLAGS, FLAG_SENSOR_AWAIT_RISING);
	Sensor_set_light_check_timer_period(SENSOR_RISING_EDGE_MAX_DELAY_TIMER_PERIOD);
	isr_lightsense_Enable();
}

static void Sensor_handle_missing_rising_edge(void)
{
	// Timer_Light_Check_Stop();
	// Sensor_write_low_all_sensors();

#ifdef SENSOR_DEBUG
	DEBUG_7_ON;
#endif
}

static void Sensor_prepare_for_sampling(void)
{
	FLAG_CLEAR(FLAGS, FLAG_SENSOR_AWAIT_RISING);
	isr_lightsense_Disable();
	Sensor_set_light_check_timer_period(SENSOR_SAMPLING_TIMER_PERIOD);

#ifdef SENSOR_DEBUG
	DEBUG_7_OFF;
#endif
}

static void Sensor_sample_sensor_readings(void)
{
	SENSOR_SAMPLE_READING(Sensor_turnLeft, Turn_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_turnRight, Turn_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewBackRight, Skew_Back_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewBackLeft, Skew_Back_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_skewFrontRight, Skew_Front_Right_Read);
	SENSOR_SAMPLE_READING(Sensor_skewFrontLeft, Skew_Front_Left_Read);
	SENSOR_SAMPLE_READING(Sensor_skewMiddle, Skew_Middle_Read);
}

static void Sensor_debounce_and_update_sensor_statuses(void)
{
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_turnLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_turnRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewBackRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewBackLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewFrontRight);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewFrontLeft);
	SENSOR_DEBOUNCE_AND_UPDATE_STATUS(Sensor_skewMiddle);
}

static void Sensor_write_low_all_sensors(void)
{
	SENSOR_WRITE_LOW(Sensor_turnLeft);
	SENSOR_WRITE_LOW(Sensor_turnRight);
	SENSOR_WRITE_LOW(Sensor_skewBackLeft);
	SENSOR_WRITE_LOW(Sensor_skewBackRight);
	SENSOR_WRITE_LOW(Sensor_skewFrontLeft);
	SENSOR_WRITE_LOW(Sensor_skewFrontRight);
	SENSOR_WRITE_LOW(Sensor_skewMiddle);
}

void Sensor_init_sensors(void)
{
	DAC_Lower_Start();
	DAC_Upper_Start();
	DAC_Middle_Start();
	Sensor_set_bias_level(SENSOR_DEFAULT_BIAS_VOLTAGE_VOLTS);
	isr_lightsense_StartEx(SENSOR_ISR_LIGHT_SENSED);
	isr_lightcheck_StartEx(SENSOR_ISR_CHECK_LIGHT);
}
