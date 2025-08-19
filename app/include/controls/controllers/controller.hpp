#ifndef CONTROLS_CONTROLLER_HPP
#define CONTROLS_CONTROLLER_HPP

#include "../ship_orders.hpp"
#include "core/ship.hpp"

namespace core {
  class Battle;
}

namespace controls {
  class Controller {
  private:
  protected:
    core::Battle* battle;
  public:
    virtual ShipOrders getOrders(core::Ship& ship) = 0;
    void setBattle(core::Battle* battle);

  friend class Battle;
  };
}

#endif
