#include "parts/cores/spaceship_core.hpp"
#include "physics/physics_object.hpp"
#include "physics/physics_transform.hpp"
#include "utility/angle.hpp"

namespace parts {
  using physics::CappedTransform;
  //TODO: properly call constructors of parent classes
  SpaceshipCore::SpaceshipCore(
    int hp,
    int mass)
  :
    PhysicsObject(std::make_unique<CappedTransform>(100000, 15)) {}

  void SpaceshipCore::resetState() {
    physics::PhysicsObject::resetTransform();
    PhysicsObject::setAngle(util::degrees(-90));
  }

}
