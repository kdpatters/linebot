// Calibration constants
#define CALIBRATION_SPEED 100
#define CALIBRATION_TIME 1000
#define CALIBRATION_FREQ 10
#define CALIBRATION_LOOPS (CALIBRATION_TIME / CALIBRATION_FREQ)
#define DIRECTION_CHANGES 2

// Navigation constants
// Value of Zumo line sensors when the robot is centered on the line
#define NAV_SPEED 200
#define LEFTMOST_POS 0
#define RIGHTMOST_POS 5000
#define CENTERED_ON_PATH ((RIGHTMOST_POS - LEFTMOST_POS) / 2)
#define MAX_ERROR (CENTERED_ON_PATH + LEFTMOST_POS)

// PID correction constants
#define PROP_GAIN 500
#define DERIV_GAIN 3000
