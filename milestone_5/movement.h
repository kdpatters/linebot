#ifndef H_MOV
#define H_MOV

#include <ZumoShield.h>

class MvmtSys {
  public:
    MvmtSys(ZumoMotors *);
    void follow_line(int);
    void turn_left();
    void turn_right();
    void turn_around();
    void stop_moving();
    void drive();
  private:
    double previous_error;
    ZumoMotors *motors;
    void turn_angle(int);
    void set_speeds(int, int);
};

#endif
