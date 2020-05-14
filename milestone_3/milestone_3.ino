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
  
  /* Keep searching for a branch until one is detected. */
  char turn = T_STRAIGHT;
  while (turn == T_STRAIGHT) {
    /* Read sensor values normalized between 0 and 1000.
     * Line position is an integer between 0 and 5000.  When the line is to
     * the left of the robot, the position is 0.  When the line is to the right
     * of the robot, the position is 5000. */
    int line_pos = ir_sensors.readLine(sensor_vals);
  
    // Determine the type of intersection encountered
    turn = detect_turn(sensor_vals);
  
    switch(turn) {
      case T_DEAD_END :
        driver.follow_line(line_pos);
        buzzer.play("L32 fb-f");
        break;
      case T_STRAIGHT :
        driver.follow_line(line_pos);
        break;
      case T_RIGHT :
        driver.turn_right();
        buzzer.play("L32 eg");
        break;
      case T_LEFT :
        driver.turn_left();
        buzzer.play("L32 db");
        break;
    }
    //buzzer.stopPlaying();
  }

  /* Now, keep line following until timer has expired... This is to keep the same
   * turn from being recognized multiple times. */
  unsigned long start = millis();
  unsigned long delta = 0;
  while (delta < INTERSECTION_DELAY) {
    int line_pos = ir_sensors.readLine(sensor_vals);
    driver.follow_line(line_pos);
    delta = millis() - start;
  }
  
}
