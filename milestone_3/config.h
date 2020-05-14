#ifndef H_CONFIG
#define H_CONFIG

// Calibration constants
#define CALIBRATION_TIME 3000
#define DIRECTION_CHANGES 2
#define CALIBRATION_DELAY (CALIBRATION_TIME / DIRECTION_CHANGES)

// Speed constants
#define CALIBRATION_SPEED 200
#define NAV_SPEED 200
#define TURN_SPEED 400
#define MAX_SPEED 1000

// Movement constants
// Value of Zumo line sensors when the robot is centered on the line
#define LEFTMOST_POS 0
#define RIGHTMOST_POS 5000
#define CENTERED_ON_PATH ((RIGHTMOST_POS - LEFTMOST_POS) / 2)
#define MAX_ERROR (CENTERED_ON_PATH + LEFTMOST_POS)
// PID correction constants
#define PROP_GAIN 500
#define DERIV_GAIN 3000

// Sensory constants
/* Relative darkness (on scale of 0 to 1000) 
 * that sensors read in to count as reading the 
 * electrical tape line */
#define THRESHOLD 500
#define N_SENSORS 6

// Navigation constants
#define IS_DARK(sensor) (sensor > THRESHOLD)
#define T_LEFT 'L'
#define T_RIGHT 'R'
#define T_DEAD_END 'U'
#define T_STRAIGHT 'S'
#define TURN_DELAY 0.9
#define DRIVE_DELAY 20
#define INTERSECTION_DELAY (800 * (200 / NAV_SPEED))

#endif
