#ifndef CONTROLS_PLAYER_CONTROLLER_HPP
#define CONTROLS_PLAYER_CONTROLLER_HPP

#include "controller.hpp"
#include <queue>

namespace controls {
  class PlayerController : public Controller {
  private:
    std::queue<sf::Event> events;
  public:
    virtual ShipOrders getOrders() override;

    void addEvent(sf::Event event);
  };
}

#endif
