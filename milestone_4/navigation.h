#ifndef H_NAV
#define H_NAV

class NavSys {
  public:
    NavSys();
    char detect_turn(int[]);
  private:
    void clear_state();
    bool checking_turn_type;
    bool path_on_left;
    bool path_on_right;
    bool path_forward;
    unsigned long goal_timer;
};

#endif
