#include "parts/cores/mouse_core.hpp"
#include "physics/physics_transform.hpp"

namespace parts {
  using util::Vec2d;

  MouseCore::MouseCore(double thrust, double angular_thrust) :
    thrust(thrust),
    angular_thrust(angular_thrust) {}

  void MouseCore::physicsTick(double dt) {
    ShipCore::physicsTick(dt, {engine_transform});
  }

  void MouseCore::handleInstructions(controls::ShipOrders input) {

    double delta = input.mouse_left - input.mouse_right;

    Vec2d forward =
      util::vecBetween(getPosition(), input.target, getThrust());
    Vec2d side = {-forward.y, forward.x};

    engine_transform.acceleration = forward * delta;
    engine_transform.acceleration.rescale(thrust);


    engine_transform.angular_acceleration =
      (input.right_arrow - input.left_arrow) * angular_thrust;
  }

  void MouseCore::resetState() {
    ShipCore::resetState();
    engine_transform.reset();
  }

  double MouseCore::getThrust() const {
    return thrust;
  }
}
