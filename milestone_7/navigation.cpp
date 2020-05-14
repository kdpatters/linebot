#include <Arduino.h>
#include <ZumoShield.h> // TODO : remove
#include "config.h"
#include "navigation.h"

NavSys::NavSys() {
  this->clear_xing_state();
}

bool NavSys::keep_turning(int v[N_SENSORS], int line_pos) {
  return (IS_DARK(v[3]) || IS_DARK(v[2]))
    && (abs(line_pos - CENTERED_ON_PATH) < POS_TURN_FINISH);
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
  if (this->checking_turn_type && left && right && (time_elapsed > GOAL_TIMEOUT)) {
    return T_GOAL;
  }
  
  // Check if currently in an intersection
  else if (left || right) {
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
  else if (this->checking_turn_type) {
    char path = T_NONE;
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
    return path;
  }

  /* No intersection present... */
  // Check if at dead end
  else if (!center) {
    return T_DEAD_END;
  }
  // No intersection found
  return T_NONE;
}

bool NavSys::is_dead_end(int v[N_SENSORS]) {
  bool dead_end = !(IS_DARK(v[1]) || IS_DARK(v[2]) \
      || IS_DARK(v[3]) || IS_DARK(v[4]));
  return dead_end;  
}

bool NavSys::is_turn(int v[N_SENSORS]) {
  bool left = IS_DARK(v[0]);
  bool right = IS_DARK(v[4]);
  return left || right;
}

/* Reduce the stored path by removing detours. */
void NavSys::reduce_path(ZumoBuzzer buzzer) {
  std::vector<char> path = this->get_path();
  
  // Iterate through elements of the vector
  for (std::vector<char>::iterator turn = path.begin(); turn != path.end(); turn++) {
    // Remove dead ends by replacing 3 consecutive turns with 1
    while ((*turn) == T_DEAD_END) {
      char prev = *(turn - 1);
      char next = *(turn + 1);
      
      // Remove 2 elements from vector and replace the 3rd
      // Update pointer to location of 3rd element which will be replaced
      turn = path.erase(turn - 1, turn + 1);

      // Match first and second intersections for pattern
      #define MATCH_T(f,s) ((prev == f) && (next == s))
      
      if (MATCH_T(T_LEFT, T_RIGHT) ||
          MATCH_T(T_RIGHT, T_LEFT) || 
          MATCH_T(T_STRAIGHT, T_STRAIGHT)) {
        (*turn) = T_DEAD_END;
      }
          
      else if (MATCH_T(T_LEFT, T_STRAIGHT) ||
                MATCH_T(T_STRAIGHT, T_LEFT)) {
        (*turn) = T_RIGHT;
      }
      
      else if (MATCH_T(T_RIGHT, T_STRAIGHT) || 
               MATCH_T(T_STRAIGHT, T_RIGHT)) {
        (*turn) = T_LEFT;
      }
        
      else if (MATCH_T(T_LEFT, T_LEFT) || 
               MATCH_T(T_RIGHT, T_RIGHT)) {
        (*turn) = T_STRAIGHT;
      }
    }
  }
  this->path.assign(path.begin(), path.end());
}

/* Return the vector for the current stored path. */
std::vector<char> NavSys::get_path() {
  return this->path;
}

/* Store each detected turn as robot reaches it. */
void NavSys::store_turn(char turn) {
  // Check for valid types before storing
  if ((turn == T_LEFT) || (turn == T_RIGHT) || (turn == T_STRAIGHT) || 
      (turn == T_DEAD_END) || (turn == T_GOAL)) {
    this->path.push_back(turn);
    }
}

/* Clear the stored state for intersection/crossing data */
void NavSys::clear_xing_state() {
  this->checking_turn_type = 0;
  this->path_on_left = 0;
  this->path_on_right = 0;
  this->path_forward = 0;
}
