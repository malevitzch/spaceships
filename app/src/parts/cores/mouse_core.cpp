#include "parts/cores/mouse_core.hpp"

namespace parts {
  MouseCore::MouseCore(double thrust) : SpaceshipCore(100, 100), thrust(thrust) {}

  void MouseCore::physicsTick(double dt) {
    getTransform().acceleration += engines * thrust;
    PhysicsObject::physicsTick(dt);
    getTransform().acceleration -= engines * thrust;
  }

  void MouseCore::handleInstructions(controls::ShipOrders input) {
    engines = util::vecBetween(getPosition(), input.target, 1.0);
  }

  void MouseCore::resetState() {
    SpaceshipCore::resetState();
    engines = {0, 0};
  }
}
