#ifndef CONTROLS_ENEMY_CONTROLLER_HPP
#define CONTROLS_ENEMY_CONTROLLER_HPP

#include "controller.hpp"

namespace core {
  class Battle;
}

namespace controls {
  class EnemyController : public Controller {
  private:
  public:
    virtual ShipOrders getOrders() override;
  };
}

#endif
