#ifndef PARTS_CORES_MOUSE_CORE
#define PARTS_CORES_MOUSE_CORE

#include "parts/cores/spaceship_core.hpp"

namespace parts {
  class MouseCore : public SpaceshipCore {
  private:
    double thrust = 0;
    util::Vec2d engines = {0, 0};
  public:
    MouseCore(double thrust);
    virtual void physicsTick(double dt) override;

    virtual void handleInstructions(controls::ShipOrders input) override;

    virtual void resetState() override;
  };
}

#endif
