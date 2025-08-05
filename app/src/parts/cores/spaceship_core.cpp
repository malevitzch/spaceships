#include "parts/cores/spaceship_core.hpp"
#include "physics/physics_object.hpp"
#include "physics/physics_transform.hpp"
#include "utility/angle.hpp"

namespace parts {
  using physics::CappedTransform;
  SpaceshipCore::SpaceshipCore() :
    PhysicsObject(std::make_unique<CappedTransform>(100000, 15)) {}

  void SpaceshipCore::resetState() {
    physics::PhysicsObject::resetTransform();
    PhysicsObject::setAngle(util::degrees(-90));
  }

}
