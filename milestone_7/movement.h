#ifndef H_MOV
#define H_MOV

#include <ZumoShield.h>

class MvmtSys {
  public:
    MvmtSys(ZumoMotors *);
    void follow_line(int, int base_speed = NAV_SPEED);
    void turn_left();
    void turn_right();
    void rotate_clockwise();
    void stop_moving();
    void drive(int def_speed = NAV_SPEED);
  private:
    double previous_error;
    ZumoMotors *motors;
    void turn_angle(int);
    void set_speeds(int, int);
};

#endif
