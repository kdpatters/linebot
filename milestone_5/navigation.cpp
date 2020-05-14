#include <Arduino.h>
#include "config.h"
#include "navigation.h"

NavSys::NavSys() {
  this->clear_xing_state();
}

char NavSys::detect_turn(int v[N_SENSORS]) {
  bool left = IS_DARK(v[0]);
  bool center = IS_DARK(v[1]) || IS_DARK(v[2]) \
      || IS_DARK(v[3]) || IS_DARK(v[4]);
  bool right = IS_DARK(v[5]);

  // Update NavSys state
  this->path_on_left |= left;
  this->path_on_right |= right;

  // Check if reached goal
  unsigned long time_elapsed = millis() - this->goal_timer;
  if (this->checking_turn_type && left && right && (time_elapsed > GOAL_TIMEOUT))
    return T_GOAL;
  
  // Check if currently in an intersection
  if (left || right) {
    // Start the goal timer if necessary
    if (!this->checking_turn_type) {
      this->goal_timer = millis();
      this->checking_turn_type = true;
    }
    // Return status as still checking intersection type
    return T_CHECKING;
  }

  /* Leaving intersection... determine which
   *  direction robot should travel next in following
   *  the left-hand wall to the maze solution.
   */
  if (this->checking_turn_type) {
    char path = T_STRAIGHT;
    // If possible to take a left, do it
    if (this->path_on_left)
      path = T_LEFT;
    // If not, try to go straight
    else if (center)
      path = T_STRAIGHT;
    // Take right branch as last resort
    else if (this->path_on_right)
      path = T_RIGHT;
    this->clear_xing_state(); // Clear variables
    this->store_turn(path);
    return path;
  }

  /* No intersection present... */
  // Check if following unbranching path
  if (center)
    return T_STRAIGHT;
  this->store_turn(T_DEAD_END);
  return T_DEAD_END;    
}

/* Return the vector for the current stored path. */
std::vector<char> NavSys::get_path() {
  return this->path;
}

/* Store each detected turn as robot reaches it. */
void NavSys::store_turn(char turn) {
  this->path.push_back(turn);
}

/* Clear the stored state for intersection/crossing data */
void NavSys::clear_xing_state() {
  this->checking_turn_type = 0;
  this->path_on_left = 0;
  this->path_on_right = 0;
  this->path_forward = 0;
}
