#ifndef H_NAV
#define H_NAV

#include <ArduinoSTL.h>

class NavSys {
  public:
    NavSys();
    char detect_turn(int[]);
    std::vector<char> get_path();
  private:
    void store_turn(char turn);
    void clear_xing_state();
    bool checking_turn_type;
    bool path_on_left;
    bool path_on_right;
    bool path_forward;
    std::vector<char> path;
    unsigned long goal_timer;
};

#endif
