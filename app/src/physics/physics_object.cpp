#include "physics/physics_object.hpp"

namespace physics {
  PhysicsObject::PhysicsObject(PhysicsTransform transform) : transform(transform) {}

  util::Vec2d PhysicsObject::getPosition() const {
    return transform.position;
  }
  void PhysicsObject::setPosition(util::Vec2d target) {
    this->transform.position = target;
  }

  util::Angle PhysicsObject::getAngle() const {
    return transform.angle;
  }
  void PhysicsObject::setAngle(util::Angle angle) {
    transform.angle = angle;
  }
}
