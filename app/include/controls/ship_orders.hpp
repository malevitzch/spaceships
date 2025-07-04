#ifndef CONTROLS_SHIP_ORDERS_HPP
#define CONTROLS_SHIP_ORDERS_HPP

#include <SFML/Graphics.hpp>

#include <queue>

namespace controls {
  // Struct that contains extracted information
  // from what the player pressed
  struct ShipOrders {
    bool left = false;
    bool right = false;

    bool ahead = false;
    bool back = false;

    bool left_arrow = false;
    bool right_arrow = false;

    ShipOrders() = default;
    ShipOrders(bool left, bool right, bool ahead, bool back);
  };

  ShipOrders getPlayerOrders(std::queue<std::optional<sf::Event>>& events);
}

#endif
