#ifndef PARTS_CORES_MOUSE_CORE
#define PARTS_CORES_MOUSE_CORE

#include "parts/cores/spaceship_core.hpp"
#include "physics/physics_transform.hpp"

namespace parts {
  class MouseCore : public SpaceshipCore {
  private:
    double thrust = 0;
    physics::PhysicsTransform engine_transform;
  public:
    MouseCore(double thrust);
    virtual void physicsTick(double dt) override;

    virtual void handleInstructions(controls::ShipOrders input) override;

    virtual void resetState() override;
  };
}

#endif
