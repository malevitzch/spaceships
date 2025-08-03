#include "parts/cores/mouse_core.hpp"
#include "physics/physics_transform.hpp"

namespace parts {
  using util::Vec2d;

  MouseCore::MouseCore(double thrust, double angular_thrust) :
    thrust(thrust),
    angular_thrust(angular_thrust),
    SpaceshipCore(100, 100) {}

  void MouseCore::physicsTick(double dt) {
    SpaceshipCore::physicsTick(dt, {engine_transform});
  }

  void MouseCore::handleInstructions(controls::ShipOrders input) {

    double dy = input.right - input.left;
    double dx = input.ahead - input.back;

    Vec2d forward =
      util::vecBetween(getPosition(), input.target, getThrust());
    Vec2d side = {-forward.y, forward.x};

    engine_transform.acceleration = forward * dx + side * dy;
    engine_transform.acceleration.rescale(thrust);


    engine_transform.angular_acceleration =
      (input.right_arrow - input.left_arrow) * angular_thrust;
  }

  void MouseCore::resetState() {
    SpaceshipCore::resetState();
    engine_transform.reset();
  }

  double MouseCore::getThrust() const {
    return thrust;
  }
}
