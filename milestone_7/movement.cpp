#include "config.h"
#include "movement.h"

MvmtSys::MvmtSys(ZumoMotors *motors) {
  this->previous_error = 0;
  this->motors = motors;
}

void MvmtSys::follow_line(int line_position, int base_speed = NAV_SPEED) {
    /* Compute the scaled amount of positional error [-1, 1]. */
    double positional_error = (line_position - CENTERED_ON_PATH) / (double) MAX_ERROR;

    /* Speed adjustment for error. */
    double error_diff = positional_error - previous_error;
    int adjustment = PROP_GAIN * positional_error + DERIV_GAIN * error_diff;
    this->set_speeds(base_speed + adjustment, base_speed - adjustment);
    this->previous_error = positional_error;
}

void MvmtSys::turn_left() {
    this->turn_angle(90);
}

void MvmtSys::turn_right() {
    this->turn_angle(-90);
}

void MvmtSys::rotate_clockwise() {
    this->set_speeds(TURN_SPEED, -TURN_SPEED);
}

void MvmtSys::stop_moving() {
    this->set_speeds(0, 0);
}

void MvmtSys::drive(int def_speed = NAV_SPEED) {
    this->set_speeds(def_speed, def_speed);
}

/* Helper function to turn a specific angle [-180, 180].  Positive angles
 * trigger a left turn and negative angles trigger a right turn. */
void MvmtSys::turn_angle(int angle) {

    int left_speed = TURN_SPEED;
    int right_speed = TURN_SPEED;
    float factor = -1;
    if (angle < 0) { // Right turn
        right_speed *= factor;
    }
    else { // Left turn
        left_speed *= factor;
    }

    // Actual turning
    this->set_speeds(left_speed, right_speed);
    delay(TURN_DELAY * abs(angle));
    
    // Decay speed as timeout comes closer; this allows
    // robot to start at a rapid speed and then slow downs
    /*unsigned long start = millis();
    unsigned long delta = millis() - start;
    int ms_delay = TURN_DELAY * abs(angle);
    // Target to slow down to 1/4 max speed
    #define FUNC(var) (var * var)
    #define COEFF(max_speed) ((max_speed * (3.0 / 4.0)) / FUNC(ms_delay))
    while (delta < ms_delay) {
      this->set_speeds(left_speed - COEFF(left_speed) * FUNC(delta), right_speed - COEFF(left_speed) * FUNC(delta));
      delta = millis() - start;
    } */
}

void MvmtSys::set_speeds(int left_speed, int right_speed) {
  /* Reduce speeds to maximums. */
  int new_right = min(MAX_SPEED, abs(right_speed));
  int new_left = min(MAX_SPEED, abs(left_speed));
  if (right_speed < 0)
    new_right = -new_right;
  if (left_speed < 0)
    new_left = -new_left;
  this->motors->setSpeeds(new_left, new_right);
}
