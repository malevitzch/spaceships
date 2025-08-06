#ifndef CONTROLS_SHIP_ORDERS_HPP
#define CONTROLS_SHIP_ORDERS_HPP


#include "utility/vec2d.hpp"

#include <cstdint>

namespace controls {
  // Struct that contains information about the controller's orders
  struct ShipOrders {

    util::Vec2d target = {0, 0};

    // Main movement orders
    bool left = false;
    bool right = false;

    bool ahead = false;
    bool back = false;

    // Secondary directional keys
    bool left_arrow = false;
    bool right_arrow = false;

    bool up_arrow = false;
    bool down_arrow = false;

    // Special keys, mostly for things such 
    // brakes, mode switching, etc
    int8_t space_p = 0;
    int8_t alt_p = 0; // left alt
    int8_t ctrl_p = 0; // left ctrl
    int8_t shift_p = 0; // left shift

    // Holddown versions of special keys for continued input
    bool space = false;
    bool alt = false;
    bool ctrl = false;
    bool shift = false;

    // Actions, they generally map to keys 1-8
    // But additional keys can be used, especially for more complicated
    // And perhaps AI-controlled ships (not "real" AI, just bots)
    // They are given as integers as there can be multiple presses
    // per frame and I don't want them lost in some cases
    int8_t actions[16] = {};

    ShipOrders() = default;

    // This function exists mostly for network-based stuff
    // It creates a copy of the current orders but without the
    // things that are one-use only
    // This is important to maintain continuity when someone has
    // high ping or lag
    ShipOrders prolong() const;
  };

}

#endif
