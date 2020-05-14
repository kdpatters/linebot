#include <Arduino.h>
#include "config.h"
#include "navigation.h"

char detect_turn(int v[N_SENSORS]) {
    bool left = IS_DARK(v[0]);
    bool center = IS_DARK(v[1]) || IS_DARK(v[2]) \
        || IS_DARK(v[3]) || IS_DARK(v[4]);
    bool right = IS_DARK(v[5]);

    // Left bend
    if (left && center)
        return T_LEFT;
    // Right bend
    else if (right && center)
        return T_RIGHT;
    // Straight path
    else if (left || right || center)
        return T_STRAIGHT;
    // Dead end
    return T_DEAD_END;
}
