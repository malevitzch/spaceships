#include "parts/cores/spaceship_core.hpp"

namespace parts {
  //TODO: properly call constructors of parent classes
  SpaceshipCore::SpaceshipCore(
    int hp,
    int mass)
  :
    physics::PhysicsObject(physics::CappedTransform(10000, 6)),
    hp(hp),
    mass(mass) {}
  int SpaceshipCore::getHp() {return hp;}
  int SpaceshipCore::getMass() {return mass;}
}
