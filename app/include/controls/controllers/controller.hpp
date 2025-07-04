#ifndef CONTROLS_CONTROLLER_HPP
#define CONTROLS_CONTROLLER_HPP

#include "../ship_orders.hpp"

namespace controls {
  class Controller {
  private:
  public:
    virtual ShipOrders getOrders() = 0;
  };
}

#endif
