#include <ZumoShield.h>

#define SPEED 200

ZumoMotors motors;

void turn_left() {
  motors.setLeftSpeed(-SPEED);
  motors.setRightSpeed(SPEED);  
}

void turn_right() {
  motors.setLeftSpeed(SPEED);
  motors.setRightSpeed(-SPEED);  
}

void drive_forward() {
  motors.setLeftSpeed(SPEED);
  motors.setRightSpeed(SPEED);
}

void stop_driving() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);  
}

void setup() {
  // Drive forward for 4 seconds
  drive_forward();
  delay(4800);

  stop_driving();
  delay(500);

  // Turn right
  turn_right();
  delay(2000);

  stop_driving();
  delay(500);

  // Turn left
  turn_left();
  delay(2000);

  // Stop driving
  stop_driving();
}

void loop() {
}
