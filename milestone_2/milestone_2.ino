#include <Wire.h>
#include <ZumoShield.h>
#include "config.h"

ZumoReflectanceSensorArray ir_sensors(QTR_NO_EMITTER_PIN);
unsigned int sensor_vals[6]; // Create an array to store sensory input
ZumoMotors motors;
double previous_error = 0;

// Perform initial calibration
void setup() {
  // Rotate robot for given number of direction changes
  for (int i = 0, rotation = 1; i < DIRECTION_CHANGES; i++) {

    motors.setSpeeds(- CALIBRATION_SPEED * rotation, 
                       CALIBRATION_SPEED * rotation);
      
    rotation = -rotation; // Flip rotation direction
    
    // Calibrate sensors at given frequency for given duration
    for (int j = 0; j < CALIBRATION_LOOPS; j++) {
      ir_sensors.calibrate();
      delay(CALIBRATION_FREQ);
    }
    
  }
  motors.setSpeeds(0, 0);

  // Wait 2 seconds before continuing...
  delay(2000);
}

/* Read in the position of the line and adjust correction propotional amount.
 * Robot must start on the line. */
void loop() {
  /* Line position is an integer between 0 and 5000.  When the line is to
   * the left of the robot, the position is 0.  When the line is to the right
   * of the robot, the position is 5000. */
  int line_position = ir_sensors.readLine(sensor_vals);

  /* Compute the scaled amount of positional error [-1, 1].*/
  double positional_error = (line_position - CENTERED_ON_PATH) / (double) MAX_ERROR;

  /* Speed adjustment for error.  */
  double error_diff = positional_error - previous_error;
  int adjustment = PROP_GAIN * positional_error + DERIV_GAIN * error_diff;
  motors.setSpeeds(NAV_SPEED + adjustment, NAV_SPEED - adjustment);
  previous_error = positional_error;
}
