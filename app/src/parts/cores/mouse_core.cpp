#include "parts/cores/mouse_core.hpp"
#include "physics/physics_transform.hpp"

namespace parts {
  MouseCore::MouseCore(double thrust) : thrust(thrust), SpaceshipCore(100, 100) {}

  void MouseCore::physicsTick(double dt) {
    PhysicsObject::physicsTick(dt, {engine_transform});
  }

  void MouseCore::handleInstructions(controls::ShipOrders input) {
    engine_transform.acceleration =
      util::vecBetween(getPosition(), input.target, thrust);
  }

  void MouseCore::resetState() {
    SpaceshipCore::resetState();
      engine_transform.reset();
    }
}
