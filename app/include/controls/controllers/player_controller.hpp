#ifndef CONTROLS_PLAYER_CONTROLLER_HPP
#define CONTROLS_PLAYER_CONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "controller.hpp"
#include <queue>

namespace core {
  class Battle;
}

namespace controls {
  class PlayerController : public Controller {
  private:
    core::Battle* battle;
    std::queue<sf::Event> events;
    void addHolddownKeys(ShipOrders& orders) const;
    void setTarget(ShipOrders& orders) const;
    void addMouseEvents(ShipOrders& orders) const;
  public:
    virtual ShipOrders getOrders() override;

    void addEvent(sf::Event event);
    friend class core::Battle;
  };
}

#endif
