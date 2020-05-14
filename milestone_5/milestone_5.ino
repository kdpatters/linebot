#include <ArduinoSTL.h>
#include <Wire.h>
#include <ZumoShield.h>
#include "config.h"
#include "navigation.h"
#include "movement.h"

ZumoReflectanceSensorArray ir_sensors(QTR_NO_EMITTER_PIN);
unsigned int sensor_vals[N_SENSORS]; // Create an array to store sensory input
ZumoMotors motors;
ZumoBuzzer buzzer;
MvmtSys driver(&motors);
NavSys nav;

// Perform initial calibration
void setup() {
  delay(500);
  
  // Rotate robot for given number of direction changes
  for (int i = 0, rotation = 1; i < DIRECTION_CHANGES; i++) {

    motors.setSpeeds(- CALIBRATION_SPEED * rotation, 
                       CALIBRATION_SPEED * rotation);
      
    rotation = -rotation; // Flip rotation direction
    
    // Calibrate sensors at given frequency for given duration
    unsigned long start = millis();
    unsigned long delta = millis() - start;
    while(delta < CALIBRATION_DELAY) {
      ir_sensors.calibrate();
      delta = millis() - start;
    }
    
  }
  driver.stop_moving();
  delay(500);
}

/* Read in the position of the line and adjust correction propotional amount.
 * Robot must start on the line. */
void loop() {
  /* Keep line following until timer has expired... This is to keep the same
   * turn from being recognized multiple times. */
  unsigned long start = millis();
  unsigned long delta = 0;
  while (delta < INTERSECTION_DELAY) {
    int line_pos = ir_sensors.readLine(sensor_vals);
    driver.follow_line(line_pos);
    delta = millis() - start;
  }
  
  /* Now, searching for a branch until one is detected. */
  char turn = T_STRAIGHT;
  while (turn == T_STRAIGHT) {
    /* Read sensor values normalized between 0 and 1000.
     * Line position is an integer between 0 and 5000.  When the line is to
     * the left of the robot, the position is 0.  When the line is to the right
     * of the robot, the position is 5000. */
    int line_pos = ir_sensors.readLine(sensor_vals);
  
    // Determine the type of intersection encountered
    turn = nav.detect_turn(sensor_vals);

    /* If at an intersection, attempt to pass through until the
     *  intersection type is unambiguous.
     */
    while (turn == T_CHECKING) {
      driver.drive(); // Continue driving forward
      line_pos = ir_sensors.readLine(sensor_vals);
      turn = nav.detect_turn(sensor_vals);
    }
  
    switch(turn) {
      // Reached a dead end and turning around
      case T_DEAD_END :
        driver.follow_line(line_pos);
        buzzer.play("L32 fb-f");
        break;
      // Using PD control to continue following the line
      case T_STRAIGHT :
        driver.follow_line(line_pos);
        break;
      // Taking a right turn
      case T_RIGHT :
        driver.turn_right();
        buzzer.play("L32 eg");
        break;
      // Taking a left turn
      case T_LEFT :
        driver.turn_left();
        buzzer.play("L32 db");
        break;
      // Reached goal
      case T_GOAL :
        driver.stop_moving();
        buzzer.play("e32e32f16a32a32c8");
        while (true) {} // Stop doing anything
        break;
    }
    //buzzer.stopPlaying();
  }  
}
