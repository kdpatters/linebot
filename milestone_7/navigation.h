#ifndef H_NAV
#define H_NAV

#include <ArduinoSTL.h>

class NavSys {
  public:
    NavSys();
    bool keep_turning(int[], int);
    char detect_turn(int[]);
    bool is_dead_end(int[]);
    bool is_turn(int[]);
    void reduce_path(ZumoBuzzer);
    std::vector<char> get_path();
    void store_turn(char turn);
  private:
    void clear_xing_state();
    bool checking_turn_type;
    bool path_on_left;
    bool path_on_right;
    bool path_forward;
    std::vector<char> path;
    unsigned long goal_timer;
};

#endif
