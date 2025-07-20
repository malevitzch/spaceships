#ifndef CONTROLS_SHIP_ORDERS_HPP
#define CONTROLS_SHIP_ORDERS_HPP

#include <SFML/Graphics.hpp>

#include <cstdint>

namespace controls {
  // Struct that contains information about the controller's orders
  struct ShipOrders {

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
    // and in keypress mode
    bool space = false;
    bool alt = false; // left alt
    bool ctrl = false; // left ctrl
    bool shift = false; // left shift

    // Actions, generally maps to keys 1-8
    // They are given as integers as there can be multiple presses
    // per frame and I don't want them lost in some cases
    int8_t actions[8] = {};

    ShipOrders() = default;
    ShipOrders(bool left, bool right, bool ahead, bool back);
  };

}

#endif
