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
Pushbutton button(ZUMO_BUTTON);
MvmtSys driver(&motors);
NavSys nav;

/* Perform initial calibration */
void calibrate_sensors() {
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
}

void setup() {
  delay(500);
  // Perform initial calibration
  calibrate_sensors();
  delay(500);
}

/* Keep line following until timer has expired... This is to keep the same
 *  turn from being recognized multiple times too quickly.
 */
void continue_on_path() {
  unsigned long start = millis();
  unsigned long delta = 0;
  while (delta < INTERSECTION_DELAY) {
    int line_pos = ir_sensors.readLine(sensor_vals);
    driver.follow_line(line_pos);
    delta = millis() - start;
  }
}

/* Take action based on info received from NavSys */
void handle_turn(char turn, int line_pos) {
    switch(turn) {
      
    // No intersection, so just use PD control to continue following the line
    case T_NONE :
      driver.follow_line(line_pos);
      break;

    // Reached a dead end so turn around
    case T_DEAD_END :
      driver.turn_right();
      driver.turn_right();
      driver.rotate_clockwise();
      while (nav.keep_turning(sensor_vals, line_pos))
        line_pos = ir_sensors.readLine(sensor_vals);
      buzzer.play("L32 fb-");
      break;

    case T_STRAIGHT :
      // Ignore the intersection
      driver.drive();
      buzzer.play("L32 ga");
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
      break;
  }
}

void loop() {  
  continue_on_path();
  
  /* Now, search for a turn until one is detected. */
  char turn = T_NONE;
  while (turn == T_NONE) {
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

    // Store data about the intersection
    nav.store_turn(turn);
    // Take action based on info from NavSys
    handle_turn(turn, line_pos);
    
    if (turn == T_GOAL)
      solved();
  }
}

void solve_maze(std::vector<char> replay) {
    /* Replay the path following button press */
    for (std::vector<char>::iterator turn = replay.begin(); turn != replay.end(); turn++) {
      // Continue on path until intersection timeout expires
      continue_on_path();
      
      // Keep following the line until a turn is reached
      int line_pos;
      while (!(nav.is_turn(sensor_vals) || nav.is_dead_end(sensor_vals))) {
        line_pos = ir_sensors.readLine(sensor_vals);
        driver.follow_line(line_pos);
      }
      // Take the actual turn
      handle_turn(*turn, line_pos);  
    }
}

/* Code to run once maze has been solved. */
void solved() {
  std::vector<char> replay = nav.get_path();
  bool solved = true;
  while (solved) {
  // Play notes corresponding to turns in maze...
  for (std::vector<char>::iterator turn = replay.begin(); turn != replay.end(); turn++){
    switch (*turn) {
      case T_LEFT :
        buzzer.playNote(NOTE_C(6), 100, 15);
        break;
      case T_RIGHT :
        buzzer.playNote(NOTE_E(6), 100, 15);
        break;
      case T_STRAIGHT :
        buzzer.playNote(NOTE_G(6), 100, 15);
        break;
      case T_DEAD_END :
        buzzer.playNote(NOTE_C(7), 100, 15);
        break;
    }
    delay(200);
  }
  
    driver.stop_moving();
    
    // Wait for button press
    button.waitForButton();
    
    solve_maze(replay);
  }
}
