#ifndef PARTS_CORES_MOUSE_CORE
#define PARTS_CORES_MOUSE_CORE

#include "parts/cores/ship_core.hpp"
#include "physics/physics_transform.hpp"

namespace parts {
  class MouseCore : public ShipCore {
  private:
    double thrust = 0;
    double angular_thrust = 0;
    physics::PhysicsTransform engine_transform;
  public:
    MouseCore(double thrust, double angular_thrust);
    virtual void physicsTick(double dt) override;
    virtual void handleInstructions(controls::ShipOrders input) override;
    virtual void resetState() override;

    virtual double getThrust() const;
  };
}

#endif
