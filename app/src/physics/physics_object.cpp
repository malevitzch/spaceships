#include "physics/physics_object.hpp"

namespace physics {
  PhysicsObject::PhysicsObject(PhysicsTransform transform) : transform(transform) {}
  void PhysicsObject::setPosition(util::Vec2d target) {
    this->transform.position = target;
  }
}
