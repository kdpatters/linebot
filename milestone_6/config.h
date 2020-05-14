#ifndef H_CONFIG
#define H_CONFIG

// Calibration constants
// Time to spend on calibration in MS
#define CALIBRATION_TIME 3000
// Number of times to change robot's direction
#define DIRECTION_CHANGES 2
// Time to wait before changing direction
#define CALIBRATION_DELAY (CALIBRATION_TIME / DIRECTION_CHANGES)

// Speed constants
#define CALIBRATION_SPEED 200
#define NAV_SPEED 200
#define TURN_SPEED 200
#define MAX_SPEED 1000

// Movement constants
// Value of Zumo line sensors when the robot is centered on the line
#define LEFTMOST_POS 0
#define RIGHTMOST_POS 5000
// PID macros
#define CENTERED_ON_PATH ((RIGHTMOST_POS - LEFTMOST_POS) / 2)
#define MAX_ERROR (CENTERED_ON_PATH + LEFTMOST_POS)
// PID correction constants
#define PROP_GAIN 500
#define DERIV_GAIN 3000
/* Coefficient multiplied by number of degrees robot desires to turn
 *  to give the number of MS for which robot must turn.
 */
#define TURN_DELAY (1.3 * (400 / TURN_SPEED))
// Lower bound for time between intersections based on 6" distance
#define INTERSECTION_DELAY (300 * (200 / NAV_SPEED))

// Sensory constants
/* Relative darkness (on scale of 0 to 1000) 
 * that sensors read in to count as reading the 
 * electrical tape line */
#define THRESHOLD 500
// Number of infared sensors in robot's front sensor array
#define N_SENSORS 6
/* Maximum offset from center for rotation at 
 *  a dead end to be considered complete.
 */
#define POS_TURN_FINISH 500

// Navigation constants
/* Macro to determine whether a value received by our sensors
 *  is above our threshold for recognizing darkness.
 */
#define IS_DARK(sensor) (sensor > THRESHOLD)
// Possible messages about intersections given by NavSys
#define T_NONE 'N'
#define T_LEFT 'L'
#define T_RIGHT 'R'
#define T_DEAD_END 'E'
#define T_STRAIGHT 'S'
#define T_GOAL 'G' 
#define T_CHECKING 'C'
/* Time in MS after detecting a 'T' intersection
 *  before considering it to be the maze goal.
 */
#define GOAL_TIMEOUT (60 *(200 / NAV_SPEED))

#endif
