#include "parts/cores/spaceship_core.hpp"
#include "physics/physics_object.hpp"
#include "utility/angle.hpp"

namespace parts {
  //TODO: properly call constructors of parent classes
  SpaceshipCore::SpaceshipCore(
    int hp,
    int mass)
  :
    PhysicsObject(physics::CappedTransform(10000, 6)),
    hp(hp),
    mass(mass) {
    PhysicsObject::setAngle(util::degrees(-90));
  }

  void SpaceshipCore::resetState() {
    physics::PhysicsObject::resetTransform();
  }

  int SpaceshipCore::getHp() { return hp; }
  int SpaceshipCore::getMass() { return mass; }

}
