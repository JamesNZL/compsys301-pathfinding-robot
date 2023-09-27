#include "movement.h"
#include "common.h"
#include <project.h>

/**
 * @brief Turns target angle to turn into pulse count
 *
 * @param angle the scalar angle in degrees to turn any direction
 */
static uint16 Movement_calculate_angle_to_pulse(uint16 angle);

/**
 * @brief Sweep left until the predicate is reached.
 *
 * @param maxPulses The maximum number of pulses to sweep, or 0 for 90 degrees.
 * @param predicate A predicate to test as the robot is swept.
 * @param resetHeading Whether to reset the heading once the maximum pulses is reached or the predicate is satisfied.
 * @return uint16 The pulses swept left until the predicate was satisfied, or -1 if never satisfied.
 */
static int16 Movement_sweep_left(uint16 maxPulses, bool predicate(void), bool resetHeading);
static int16 Movement_sweep_right(uint16 maxPulses, bool predicate(void), bool resetHeading);

/**
 * @brief Calculates target duty cycle
 *
 * @param target the target pulses to be converted
 */
static float Movement_calculate_duty(uint16 target);

/**
 * @brief Sets the motor pulse target for control loop
 *
 * @param target the target amount of pulses to turn in one second
 */
static void Movement_set_M1_pulse_varying(uint16 target);
static void Movement_set_M2_pulse_varying(uint16 target);
/**
 * @brief Sets the motor pulse target for control loop - doesnt change
 *
 * @param target the target amount of pulses to turn in one second
 */
static void Movement_set_M1_pulse_target(uint16 target);
static void Movement_set_M2_pulse_target(uint16 target);

static void Movement_set_pwm_1_duty_cycle(uint8 percent);
static void Movement_set_pwm_2_duty_cycle(uint8 percent);
static uint8 Movement_calculate_compare(uint8 percent);

volatile static int16 Movement_pulsesApparentM1;
volatile static int16 Movement_pulsesApparentM2;
static int16 Movement_pulsesVaryingM1;
static int16 Movement_pulsesVaryingM2;
static int16 Movement_pulsesTargetM1;
static int16 Movement_pulsesTargetM2;

static int16 Movement_pulsesToMove;
static uint16 Movement_currentSpeed = MOVEMENT_SPEED_RUN;

static int16 Movement_pulsesSinceTurn = MOVEMENT_TURNS_REFRACTORY_PULSES;
static int8 Movement_skewDamperFactor = MOVEMENT_SKEW_DAMPING_FACTOR;
static int16 Movement_stability_counter = 0;
static uint8 Movement_leftSkewBoost;
static uint8 Movement_rightSkewBoost;

CY_ISR(MOVEMENT_ISR_PROCESS_PULSE)
{
	Movement_pulsesApparentM1 = QuadDec_M1_GetCounter();
	Movement_pulsesApparentM2 = QuadDec_M2_GetCounter();

	FLAG_SET(FLAGS, FLAG_ENCODERS_READY);

	QuadDec_M1_SetCounter(0);
	QuadDec_M2_SetCounter(0);
	Timer_Dec_ReadStatusRegister();
}

uint16 Movement_cm_to_pulse(float cm)
{
	return (uint16)(cm * MOVEMENT_CM_CONVERSION);
}

void Movement_move_mm(uint16 distance)
{
	// Enable the motors, and set the target distance, turn off move infinitely
	MOVEMENT_ENABLE;
	Movement_pulsesToMove = (float)distance / MOVEMENT_MM_PER_PULSE;

	FLAG_CLEAR(FLAGS, FLAG_MOVE_INFINITELY);
}

void Movement_check_distance(void)
{
	if (FLAG_IS_SET(FLAGS, FLAG_MOVE_INFINITELY))
	{
		return;
	}

	if (Movement_pulsesToMove <= 0)
	{
		Movement_sync_motors(MOVEMENT_SPEED_OFF);

#ifdef MOVEMENT_DEBUG_SKEW
		DEBUG_ALL_ON;
#endif

		MOVEMENT_DISABLE;
	}
}

void Movement_next_control_cycle(void)
{
	if (FLAG_IS_CLEARED(FLAGS, FLAG_ENCODERS_READY))
	{
		return;
	}

	// Subtract read pulses from distance to travel
	if (Movement_pulsesToMove > 0)
	{
		Movement_pulsesToMove -= Movement_pulsesApparentM1;
	}

	// Samples taken every 25th of a second. Divide target by 25 to get expected 25th of a second pulses
	int8 pulseError1 = (Movement_pulsesTargetM1 / 25) - Movement_pulsesApparentM1;
	int8 pulseError2 = (Movement_pulsesTargetM2 / 25) - Movement_pulsesApparentM2;
	// int8 pulseError2 = MOVEMENT_PULSE_APPARENT_1 - MOVEMENT_PULSE_APPARENT_2; // For shimmy shimmy

	uint16 target1 = Movement_pulsesVaryingM1 + pulseError1;
	uint16 target2 = Movement_pulsesVaryingM2 + pulseError2;

	Movement_write_M1_pulse(target1);
	Movement_write_M2_pulse(target2);

	// Make the varying pulses change up or down accordingly to the observed speed
	Movement_set_M1_pulse_varying(target1);
	Movement_set_M2_pulse_varying(target2);

	// Check if period beyond turn has been met -> stabilize robot
	Movement_skew_stability_timeout();

	FLAG_CLEAR(FLAGS, FLAG_ENCODERS_READY);
}

void Movement_sync_motors(uint16 speed)
{
	FLAG_CLEAR(FLAGS, FLAG_SKEW_CORRECTING);
	Movement_rightSkewBoost = 0;
	Movement_leftSkewBoost = 0;

	Movement_currentSpeed = speed;

	Movement_set_M1_pulse_target(Movement_currentSpeed);
	Movement_set_M2_pulse_target(Movement_currentSpeed);
}

void Movement_skew_correct(Direction direction)
{
	// Increase the speed of one motor to correct for a skew

	Movement_sync_motors(Movement_currentSpeed);

	FLAG_SET(FLAGS, FLAG_SKEW_CORRECTING);

	switch (direction)
	{
	case DIRECTION_LEFT:
	{
		if (FLAG_IS_CLEARED(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT))
		{
			Movement_rightSkewBoost = MOVEMENT_SKEW_NUMERIC_PULSES;
			Movement_leftSkewBoost = 0;
		}
		else
		{
			Movement_rightSkewBoost = MOVEMENT_SKEW_NUMERIC_PULSES - 5;
			Movement_leftSkewBoost = 0;
		}
		Movement_set_M2_pulse_target((Movement_currentSpeed * (100 + MOVEMENT_SKEW_CORRECTION_FACTOR - Movement_skewDamperFactor)) / 100);
		Movement_set_M1_pulse_target(Movement_currentSpeed);
		break;
	}
	case DIRECTION_RIGHT:
	{
		if (FLAG_IS_CLEARED(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT))
		{
			Movement_leftSkewBoost = MOVEMENT_SKEW_NUMERIC_PULSES;
			Movement_rightSkewBoost = 0;
		}
		else
		{
			Movement_leftSkewBoost = MOVEMENT_SKEW_NUMERIC_PULSES - 5;
			Movement_rightSkewBoost = 0;
		}
		Movement_set_M1_pulse_target((Movement_currentSpeed * (100 + MOVEMENT_SKEW_CORRECTION_FACTOR - Movement_skewDamperFactor)) / 100);
		Movement_set_M2_pulse_target(Movement_currentSpeed);
		break;
	}
	default:
	{
		break;
	}
	}
}

void Movement_skew_stability_timeout(void)
{
	if (FLAG_IS_CLEARED(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT))
	{
		return;
	}

	if (Movement_stability_counter < MOVEMENT_SKEW_STABILITY_PULSE_TIMEOUT)
	{
		Movement_stability_counter += Movement_pulsesApparentM1;
		return;
	}

	if (Sensor_are_skew_diagonals_on_line())
	{
		Movement_skewDamperFactor = MOVEMENT_SKEW_DAMPING_FACTOR;
		FLAG_CLEAR(FLAGS, FLAG_TOGGLE_TURN_TIMEOUT);
		Movement_stability_counter = 0;
	}
}

void Movement_check_turn_complete(void)
{
	if (FLAG_IS_CLEARED(FLAGS, FLAG_ENCODERS_READY))
	{
		return;
	}
	Movement_pulsesSinceTurn -= Movement_pulsesApparentM1;

	if (Movement_pulsesSinceTurn > 0)
	{
		return;
	}

	FLAG_CLEAR(FLAGS, FLAG_WAITING_AFTER_TURN);
	Movement_pulsesSinceTurn = MOVEMENT_TURNS_REFRACTORY_PULSES;
}

static uint16 Movement_calculate_angle_to_pulse(uint16 angle)
{
	switch (angle)
	{
	case 90:
	{
		return MOVEMENT_PULSE_90_DEGREE - MOVEMENT_TURNS_CORRECTION;
	}
	case 180:
	{
		return MOVEMENT_PULSE_180_DEGREE - MOVEMENT_TURNS_CORRECTION;
	}
	default:
	{
		// Convert angle to fraction of circle by dividing 360
		// Multiply fraction by total pivot circumference
		// Divide by circumference of wheel to determine revs needed
		// Convert revs to pulses through multiply 228
		uint16 rawPulses = ((((angle / (float)360) * MOVEMENT_PIVOT_CIRCUMFERENCE) / MOVEMENT_WHEEL_CIRCUMFERENCE) * MOVEMENT_PULSE_REVOLUTION);

		return (rawPulses > MOVEMENT_TURNS_CORRECTION)
			? rawPulses - MOVEMENT_TURNS_CORRECTION
			: rawPulses;
	}
	}
}

// TODO: SKEW DIRECTLY TO TURN WILL WRITE ONE MOTOR FASTER - Must use the constant values, but toggle them off in states.
void Movement_turn_left(uint16 maxAngle, bool predicate(void))
{
	// SKEW VARIABLES
	Movement_leftSkewBoost = 0;
	Movement_rightSkewBoost = 0;
	Movement_skewDamperFactor = 0;

	// Disable interrupts so decoders dont get reset to 0
	isr_getpulse_Disable();

	uint16 maxPulses = Movement_calculate_angle_to_pulse((maxAngle * (100 + MOVEMENT_TURNS_OVERSHOOT_FACTOR)) / 100);
	if (maxPulses > MOVEMENT_TURNS_LEFT_CORRECTION)
	{
		maxPulses -= MOVEMENT_TURNS_LEFT_CORRECTION;
	}

	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);
	Movement_set_direction_left(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_TURN);
	Movement_write_M2_pulse(MOVEMENT_SPEED_TURN);

	// Poll until pulse target is met
	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() > -maxPulses)
	{
#ifdef MOVEMENT_TURN_WITH_SENSORS
		// TODO: properly handle + intersection
		if (predicate())
		{
			break;
		}
#endif
	}

	Movement_set_direction_left(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
	CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

	// Reset decoders to previous value before tur
	QuadDec_M1_SetCounter(pulseMeas);
	isr_getpulse_Enable();
}

void Movement_turn_right(uint16 maxAngle, bool predicate(void))
{
	// SKEW VARIABLES
	Movement_leftSkewBoost = 0;
	Movement_rightSkewBoost = 0;
	Movement_skewDamperFactor = 0;

	isr_getpulse_Disable();

	uint16 maxPulses = Movement_calculate_angle_to_pulse((maxAngle * (100 + MOVEMENT_TURNS_OVERSHOOT_FACTOR)) / 100);
	if (maxPulses > MOVEMENT_TURNS_RIGHT_CORRECTION)
	{
		maxPulses -= MOVEMENT_TURNS_RIGHT_CORRECTION;
	}

	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);
	Movement_set_direction_right(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_TURN);
	Movement_write_M2_pulse(MOVEMENT_SPEED_TURN);

	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() < maxPulses)
	{
#ifdef MOVEMENT_TURN_WITH_SENSORS
		// TODO: properly handle + intersection
		if (predicate())
		{
			break;
		}
#endif
	}

	Movement_set_direction_right(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
	CyDelay(MOVEMENT_TURNS_STATIC_PERIOD);

	QuadDec_M1_SetCounter(pulseMeas);
	isr_getpulse_Enable();
}

static int16 Movement_sweep_left(uint16 maxPulses, bool predicate(void), bool resetHeading)
{
#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
	DEBUG_RIGHT_OFF;
#endif

	if (predicate())
	{
		return 0;
	}

	// Disable interrupt so decoders dont get reset to 0
	isr_getpulse_Disable();

	if (maxPulses == 0)
	{
		maxPulses = Movement_calculate_angle_to_pulse(90);
	}

	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	Movement_set_direction_left(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_BRAKE);
	Movement_write_M2_pulse(MOVEMENT_SPEED_BRAKE);

	// Poll until pulse target is met
	QuadDec_M1_SetCounter(0);
	bool predicateResult = FALSE;
	int16 pulsesSwept = 0;
	while ((pulsesSwept = QuadDec_M1_GetCounter()) > -maxPulses)
	{
		if (predicate())
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_LEFT_ON;
#endif
			predicateResult = TRUE;
			break;
		}
	}

	Movement_set_direction_left(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
	CyDelay(5 * MOVEMENT_TURNS_STATIC_PERIOD);

	if (!resetHeading)
	{
		// Reset decoders to previous value before turn
		QuadDec_M1_SetCounter(pulseMeas);
		isr_getpulse_Enable();

		return (predicateResult)
			? -pulsesSwept
			: -1;
	}

	// Reset turn
#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
	DEBUG_LEFT_OFF;
#endif
	Movement_set_direction_right(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_BRAKE);
	Movement_write_M2_pulse(MOVEMENT_SPEED_BRAKE);

	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() < -pulsesSwept)
	{
		;
	}

	Movement_set_direction_right(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	// Reset decoders to previous value before tur
	QuadDec_M1_SetCounter(pulseMeas);
	isr_getpulse_Enable();

	return (predicateResult)
		? -pulsesSwept
		: -1;
}

static int16 Movement_sweep_right(uint16 maxPulses, bool predicate(void), bool resetHeading)
{
#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
	DEBUG_LEFT_OFF;
#endif

	if (predicate())
	{
		return 0;
	}

	isr_getpulse_Disable();

	if (maxPulses == 0)
	{
		maxPulses = Movement_calculate_angle_to_pulse(90);
	}

	uint16 pulseMeas = QuadDec_M1_GetCounter();

	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	Movement_set_direction_right(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_BRAKE);
	Movement_write_M2_pulse(MOVEMENT_SPEED_BRAKE);

	QuadDec_M1_SetCounter(0);
	int8 predicateResult = FALSE;
	uint16 pulsesSwept = 0;
	while ((pulsesSwept = QuadDec_M1_GetCounter()) < maxPulses)
	{
		if (predicate())
		{
#ifdef MOVEMENT_DEBUG_SKEW
			DEBUG_ALL_OFF;
			DEBUG_RIGHT_ON;
#endif
			predicateResult = TRUE;
			break;
		}
	}

	Movement_set_direction_right(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);
	CyDelay(5 * MOVEMENT_TURNS_STATIC_PERIOD);

	if (!resetHeading)
	{
		QuadDec_M1_SetCounter(pulseMeas);
		isr_getpulse_Enable();

		return (predicateResult)
			? pulsesSwept
			: -1;
	}

	// Reset turn
#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
	DEBUG_RIGHT_OFF;
#endif
	Movement_set_direction_left(DIRECTION_REVERSE);
	Movement_write_M1_pulse(MOVEMENT_SPEED_BRAKE);
	Movement_write_M2_pulse(MOVEMENT_SPEED_BRAKE);

	QuadDec_M1_SetCounter(0);
	while (QuadDec_M1_GetCounter() > -pulsesSwept)
	{
		;
	}

	Movement_set_direction_left(DIRECTION_FORWARD);
	Movement_write_M1_pulse(MOVEMENT_SPEED_OFF);
	Movement_write_M2_pulse(MOVEMENT_SPEED_OFF);

	QuadDec_M1_SetCounter(pulseMeas);
	isr_getpulse_Enable();

	return (predicateResult)
		? pulsesSwept
		: -1;
}

SensorActions Movement_sweep(bool predicate(void), SensorActions actionIfUnsatisfied)
{
#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
#endif

	CyDelay(2 * MOVEMENT_TURNS_STATIC_PERIOD);
	int16 pulsesRight = Movement_sweep_right(0, predicate, TRUE);
	// + 1 to convert the -1 to 0
	int16 pulsesLeft = Movement_sweep_left(pulsesRight + 1, predicate, TRUE);

#ifdef MOVEMENT_DEBUG_SKEW
	DEBUG_ALL_OFF;
	DEBUG_INNER_ON;
#endif

	if ((pulsesLeft == -1) && (pulsesRight == -1))
	{
		CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
		return actionIfUnsatisfied;
	}
	else if (pulsesLeft == pulsesRight)
	{
		CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
		return SENSOR_ACTION_CONTINUE_FORWARD;
	}
	// Only left pulses detected
	// OR left line was closer than right line
	else if (((pulsesLeft != -1) && (pulsesRight == -1)) || ((pulsesLeft != -1) && (pulsesLeft < pulsesRight)))
	{
		// DEBUG_ALL_OFF;
		// DEBUG_OUTER_ON;
		// DEBUG_RIGHT_OFF;
		// Add 1 to ensure is never 0
		// Sweep 75% of the distance to the valid state
		Movement_sweep_left(((pulsesLeft * (100 + MOVEMENT_SWEEP_OVERSHOOT_FACTOR)) / 133) + 1, predicate, FALSE);

		CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
		return SENSOR_ACTION_CORRECT_LEFT;
	}
	else if ((pulsesRight != -1 && pulsesLeft == -1) || ((pulsesRight != -1) && (pulsesRight < pulsesLeft)))
	{
		CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
		Movement_sweep_right(((pulsesRight * (100 + MOVEMENT_SWEEP_OVERSHOOT_FACTOR)) / 133) + 1, predicate, FALSE);

		CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
		return SENSOR_ACTION_CORRECT_RIGHT;
	}

	CyDelay(3 * MOVEMENT_TURNS_STATIC_PERIOD);
	return SENSOR_ACTION_FIND_VALID_STATE;
}

static float Movement_calculate_duty(uint16 target)
{
	float dutyFraction = ((float)target / PWM_1_ReadPeriod());
	if (dutyFraction < 1)
	{
		return dutyFraction;
	}
	else
	{
		return 1;
	}
}

void Movement_write_M1_pulse(uint16 target)
{
	PWM_1_WriteCompare(PWM_1_ReadPeriod() * Movement_calculate_duty(target) + Movement_leftSkewBoost);
}

void Movement_write_M2_pulse(uint16 target)
{
	PWM_2_WriteCompare(PWM_2_ReadPeriod() * Movement_calculate_duty(target) + Movement_rightSkewBoost);
}

static void Movement_set_M1_pulse_varying(uint16 target)
{
	Movement_pulsesVaryingM1 = target;
}

static void Movement_set_M2_pulse_varying(uint16 target)
{
	Movement_pulsesVaryingM2 = target;
}

static void Movement_set_M1_pulse_target(uint16 target)
{
	Movement_pulsesTargetM1 = target;
}

static void Movement_set_M2_pulse_target(uint16 target)
{
	Movement_pulsesTargetM2 = target;
}

static void Movement_set_pwm_1_duty_cycle(uint8 percent)
{
	// set the compare
	uint8 compare = Movement_calculate_compare(percent);
	PWM_1_WriteCompare(compare);
}

static void Movement_set_pwm_2_duty_cycle(uint8 percent)
{
	// set the compare
	uint8 compare = Movement_calculate_compare(percent);
	PWM_2_WriteCompare(compare);
}

static uint8 Movement_calculate_compare(uint8 percent)
{
	// get max count assuming it is 8 bits
	uint8 maxCount = PWM_2_ReadPeriod();
	uint8 compare = (float)maxCount * ((float)percent / 100);
	return compare;
}

void Movement_set_direction_left(Direction direction)
{
	uint8 currentValue = Motor_Control_Reg_Read();
	switch (direction)
	{
	case DIRECTION_FORWARD:
	{
		currentValue |= 1 << MOTOR_LEFT_CR_POS;
		break;
	}
	case DIRECTION_REVERSE:
	{
		currentValue &= ~(1 << MOTOR_LEFT_CR_POS);
		break;
	}
	default:
		break;
	}
	Motor_Control_Reg_Write(currentValue);
}

void Movement_set_direction_right(Direction direction)
{
	uint8 currentValue = Motor_Control_Reg_Read();
	switch (direction)
	{
	case DIRECTION_FORWARD:
	{
		currentValue |= 1 << MOTOR_RIGHT_CR_POS;
		break;
	}
	case DIRECTION_REVERSE:
	{
		currentValue &= ~(1 << MOTOR_RIGHT_CR_POS);
		break;
	}
	default:
		break;
	}
	Motor_Control_Reg_Write(currentValue);
}

void Movement_set_direction(Direction direction)
{
	Movement_set_direction_left(direction);
	Movement_set_direction_right(direction);
}

void Movement_set_speed_left(uint8 percent)
{
	// While (encoder target < encoder reading){
	// Increase duty cycle
	//}
	Movement_set_pwm_1_duty_cycle(percent);
}

void Movement_set_speed_right(uint8 percent)
{
	Movement_set_pwm_2_duty_cycle(percent);
}

void Movement_set_speed(uint8 percent)
{
	Movement_set_speed_left(percent);
	Movement_set_speed_right(percent);
}

void Movement_init_motors(void)
{
	PWM_1_Start();
	PWM_2_Start();
	Timer_Dec_Start();
	QuadDec_M1_Start();
	QuadDec_M2_Start();
	isr_getpulse_StartEx(MOVEMENT_ISR_PROCESS_PULSE);
}