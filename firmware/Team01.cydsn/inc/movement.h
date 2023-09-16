#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <cytypes.h>

#define MOTOR_LEFT_CR_POS			 0
#define MOTOR_RIGHT_CR_POS			 1

#define MOVEMENT_PIVOT_CIRCUMFERENCE 354.277F
#define MOVEMENT_WHEEL_CIRCUMFERENCE 203.57F
#define MOVEMENT_PULSE_REVOLUTION	 228
#define MOVEMENT_PULSE_90_DEGREE	 99
#define MOVEMENT_PULSE_180_DEGREE	 198

#define MOVEMENT_MM_PER_PULSE		 0.8928F

#define MOVEMENT_CMS_CONVERSION	     112.0072F

#define MOVEMENT_MOTOR_OFF			 0

/**
 * @brief The possible movement directions for the robot.
 */
typedef enum Direction
{
	DIRECTION_FORWARD,
	DIRECTION_REVERSE,
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
} Direction;

volatile const extern float MOVEMENT_OFFSET;
volatile const extern float MOVEMENT_SLOPE;
volatile int16 MOVEMENT_PULSES_TO_MOVE;
volatile int16 MOVEMENT_APPARENT_PULSE_1;
volatile int16 MOVEMENT_APPARENT_PULSE_2;

volatile int16 MOVEMENT_TPULSE_1;
volatile int16 MOVEMENT_TPULSE_2;
volatile int16 MOVEMENT_CPULSE_1;
volatile int16 MOVEMENT_CPULSE_2;

const extern uint8 MOVEMENT_BRAKE_SPEED;
const extern uint16 MOVEMENT_RUN_SPEED;
const extern uint16 MOVEMENT_MOTOR_TURN_SPEED;

const extern uint8 MOVEMENT_PULSE_CORRECTION;
const extern uint8 Kp;

/**
 * @brief Checks if there is distance to move - sets speed accordingly
 */
void Movement_check_dist();

/**
 * @brief Executes the next control loop cycle with feedback
 */
void Movement_next_control_cycle();

/**
 * @brief Corrects the skew of the robot
 *
 * @param direction the direction the robot is skewing in
 */
void Movement_skewer(Direction direction);

/**
 * @brief Resets both motor speeds in cm/s - to be called after skew corrected alignment is met
 */
void Movement_sync_motors(float speed);

/**
 * @brief Instructs the robot to move a certain number of mm
 *
 * @param dist the distance to move in mm
 */
void Movement_move_mm(uint16 dist);

/**
 * @brief Sets the motor pulse target
 *
 * @param target The target amount of pulses for a motor to turn in one second
 */
void Movement_set_M1_pulse(uint16 target);
void Movement_set_M2_pulse(uint16 target);

/**
 * @brief Sets the motor pulse target for control loop
 *
 * @param target the target amount of pulses to turn in one second
 */
void Movement_set_M1_ctrltarget(uint16 target);
void Movement_set_M2_ctrltarget(uint16 target);

/**
 * @brief Sets the motor pulse target for control loop - doesnt change
 *
 * @param target the target amount of pulses to turn in one second
 */
void Movement_set_M1_ctrlconst(uint16 target);
void Movement_set_M2_ctrlconst(uint16 target);

/**
 * @brief Calculates target duty cycle
 *
 * @param target the target pulses to be converted
 */
float Movement_calculate_duty(uint16 target);

/**
 * @brief Turns the robot left (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn left from the current position
 */
void Movement_turn_left(uint16 angle);

/**
 * @brief Turns the robot right (on the spot) by angle degrees
 *
 * @param angle The angle (in degrees) to turn right from the current position
 */
void Movement_turn_right(uint16 angle);

/**
 * @brief Turns target angle to turn into pulse count
 *
 * @param angle the scalar angle in degrees to turn any direction
 */
uint16 Movement_calculate_angle_to_pulse(uint16 angle);

/**
 * @brief Turns on all skew dependencies
 */
void Movement_init_decoder_ISR();

/**
 * @brief sets the direction of BOTH motors to forwards or reverse
 *
 * @param direction the direction to set the motors to
 */
void Movement_set_direction(Direction direction);
void Movement_set_direction_right(Direction direction);
void Movement_set_direction_left(Direction direction);

/**
 * @brief sets the direction of BOTH motors to a percentage of the max speed
 *
 * @param percent percentage (out of 100) to set the motors to
 */
void Movement_set_speed(uint8 percent);
void Movement_set_speed_right(uint8 percent);
void Movement_set_speed_left(uint8 percent);

// Utils
void Movement_set_pwm_1_duty_cycle(uint8 percent);
void Movement_set_pwm_2_duty_cycle(uint8 percent);
uint8 Movement_calculate_compare(uint8 percent);

// Debug
int16 Movement_get_speed_left();
int16 Movement_get_speed_right();

#endif
