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
    // TODO: they should be able to operate both in holddown mode
    // and in keypress mode (A bool holddown)
    int8_t space = 0;
    int8_t alt = 0; // left alt
    int8_t ctrl = 0; // left ctrl
    int8_t shift = 0; // left shift

    // Actions, they generally map to keys 1-8
    // But additional keys can be used 
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
