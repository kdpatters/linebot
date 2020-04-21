#include <ZumoShield.h>

ZumoMotors motors;

void turn_left() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(100);  
}

void turn_right() {
  motors.setLeftSpeed(100);
  motors.setRightSpeed(0);  
}

void drive_forward() {
  motors.setLeftSpeed(100);
  motors.setRightSpeed(100);
}

void stop_driving() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);  
}

void setup() {
  // Drive forward for 4 seconds
  drive_forward();
  delay(4000);

  // Turn right for 2 seconds
  turn_right();
  delay(3500);

  // Turn left for 2 seconds
  turn_left();
  delay(3500);

  // Stop driving
  stop_driving();
}

void loop() {
}
