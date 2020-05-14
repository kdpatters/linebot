#ifndef H_MOV
#define H_MOV

#include <ZumoShield.h>
#include "config.h"

class MvmtSys {
  public:
    MvmtSys(ZumoMotors *);
    void follow_line(int);
    void turn_left();
    void turn_right();
    void turn_around();
    void stop_moving();
  private:
    double previous_error;
    ZumoMotors *motors;
    void drive();
    void turn_angle(int);
    void set_speeds(int, int);
};

#endif
